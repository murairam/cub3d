#include "../../incs/cub3d_bonus.h"

static void	calc_bounds(int screen_x, int sprite_width, int sprite_height,
	t_bounds *bounds)
{
	bounds->start_x = screen_x - sprite_width / 2;
	bounds->end_x = screen_x + sprite_width / 2;
	bounds->start_y = HEIGHT / 2 - sprite_height / 2;
	bounds->end_y = HEIGHT / 2 + sprite_height / 2;
	if (bounds->start_x < 0)
		bounds->start_x = 0;
	if (bounds->end_x > WIDTH)
		bounds->end_x = WIDTH;
	if (bounds->start_y < 0)
		bounds->start_y = 0;
	if (bounds->end_y > HEIGHT)
		bounds->end_y = HEIGHT;
}

static void	apply_offsets(t_game *game, t_chalk_sprite *sprite,
	double distance, t_bounds *bounds)
{
	int		pitch_offset;
	double	world_y_diff;
	double	distance_scale;
	int		vertical_offset;

	pitch_offset = -(int)(game->player.pitch * HEIGHT * 0.3f);
	world_y_diff = sprite->y - sprite->base_y;
	distance_scale = 1.0 / (distance + 0.5);
	if (distance_scale > 2.0)
		distance_scale = 2.0;
	else if (distance_scale < 0.3)
		distance_scale = 0.3;
	vertical_offset = -(int)(world_y_diff * 30 * distance_scale);
	bounds->start_y += pitch_offset + vertical_offset;
	bounds->end_y += pitch_offset + vertical_offset;
}

static void	draw_sprite_pixel(t_game *game, t_chalk_sprite *sprite,
	t_draw_params *params)
{
	int		tex_x;
	int		tex_y;
	int		tex_index;
	int		pixel_color;
	float	factor;

	if (params->sprite_width <= 0 || params->sprite_height <= 0)
		return ;
	if (!sprite->data || sprite->width <= 0 || sprite->height <= 0)
		return ;
	tex_x = (params->x - params->start_x) * sprite->width
		/ params->sprite_width;
	tex_y = (params->y - params->start_y) * sprite->height
		/ params->sprite_height;
	if (tex_x < 0 || tex_x >= sprite->width || tex_y < 0
		|| tex_y >= sprite->height)
		return ;
	tex_index = tex_y * sprite->width + tex_x;
	if (tex_index < 0 || tex_index >= (sprite->width * sprite->height))
		return ;
	factor = factor_calculator(NULL, game);
	pixel_color = dim_color(sprite->data[tex_index], factor);
	if ((pixel_color & 0x00FFFFFF) != 0x000000)
		draw_pixel(params->x, params->y, pixel_color, game);
}

static void	render_sprite_pixels(t_game *game, t_chalk_sprite *sprite,
	t_bounds *bounds, t_draw_params *params)
{
	params->y = bounds->start_y;
	while (params->y < bounds->end_y)
	{
		params->x = bounds->start_x;
		while (params->x < bounds->end_x)
		{
			draw_sprite_pixel(game, sprite, params);
			params->x++;
		}
		params->y++;
	}
}

void	render_chalk_sprite(t_game *game, t_chalk_sprite *sprite)
{
	int				screen_x;
	double			distance;
	t_bounds		bounds;
	t_draw_params	params;

	if (!game || !sprite || !sprite->data || !game->data)
		return ;
	calc_screen_pos(game, sprite, &screen_x, &distance);
	if (distance > MAX_RENDER_DISTANCE)
		return ;
	calc_sprite_size(distance, &params.sprite_width, &params.sprite_height);
	calc_bounds(screen_x, params.sprite_width, params.sprite_height, &bounds);
	apply_offsets(game, sprite, distance, &bounds);
	if (bounds.start_x >= WIDTH || bounds.end_x < 0 || bounds.start_y >= HEIGHT
		|| bounds.end_y < 0)
		return ;
	params.start_x = bounds.start_x;
	params.start_y = bounds.start_y;
	render_sprite_pixels(game, sprite, &bounds, &params);
}
