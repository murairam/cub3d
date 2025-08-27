#include "cub3d_bonus.h"

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
