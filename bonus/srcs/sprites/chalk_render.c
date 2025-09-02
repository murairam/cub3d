#include "cub3d_bonus.h"

int	is_in_fov(t_game *game, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle_to_sprite;
	double	angle_diff;

	dx = sprite_x - game->player.x;
	dy = sprite_y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > MAX_RENDER_DISTANCE)
		return (0);
	angle_to_sprite = atan2(dy, dx);
	angle_diff = normalize_angle(angle_to_sprite - game->player.angle);
	return (fabs(angle_diff) <= FOV_HALF_RADIANS);
}

void	calc_screen_pos(t_game *game, t_chalk_sprite *sprite,
	int *screen_x, double *distance)
{
	double	dx;
	double	dy;
	double	sprite_angle;
	double	angle_diff;

	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	*distance = sqrt(dx * dx + dy * dy);
	sprite_angle = atan2(dy, dx);
	angle_diff = normalize_angle(sprite_angle - game->player.angle);
	*screen_x = (int)(WIDTH / 2 + (angle_diff * WIDTH) / FOV_RADIANS);
}

void	calc_sprite_size(double distance, int *width, int *height)
{
	int	base_size;

	if (distance < 1.0)
		distance = 1.0;
	base_size = (int)(SPRITE_SCALE_FACTOR * CUBE / distance);
	*width = base_size * 2;
	*height = base_size;
	if (*width < 4)
		*width = 4;
	if (*height < 2)
		*height = 2;
	if (*width > WIDTH / 3)
	{
		*width = WIDTH / 3;
		*height = *width / 2;
	}
}
