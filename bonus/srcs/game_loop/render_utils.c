#include "cub3d_bonus.h"

int	dim_color(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

float	factor_calculator(t_ray *ray, t_game *game)
{
	float	distance;
	float	factor;

	distance = ray->perp_wall_dist;
	if (distance <= 3)
		factor = 1.0 - (distance / 3) * 0.1;
	else if (distance <= 4)
		factor = 0.9 - (distance - 3) * 0.4;
	else
		factor = 0.5 * exp(-1.5 * (distance - 4));
	if (ray->side == 0)
		factor *= 0.8f;
	pthread_mutex_lock(&game->darken_lock);
	factor *= game->darken_factor;
	pthread_mutex_unlock(&game->darken_lock);
	return (factor);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, game);
	}
}
