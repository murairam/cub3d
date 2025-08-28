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
	int	*pixel;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	if (!game || !game->data)
		return ;
	pixel = (int *)(game->data + y * game->size_line + x * (game->bpp / 8));
	*pixel = color;
}

void	clear_image(t_game *game)
{
	if (!game || !game->data)
		return ;
	ft_memset(game->data, 0, HEIGHT * game->size_line);
}


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

void	vertical_texture(t_ray *ray, t_text *text)
{
	ray->step = 1.0f * text->height / ray->l_height;
	ray->tx_pos = (ray->d_start - HEIGHT / 2 + ray->l_height / 2) * ray->step;
}

void	texture_cord(t_ray *ray, t_player *player, t_text *text)
{
	if (ray->side == 0)
		ray->wall_x = player->y / CUBE + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->x / CUBE + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (float)(text->width));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = text->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = text->width - ray->tex_x - 1;
}
