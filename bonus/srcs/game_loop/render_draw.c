#include "cub3d_bonus.h"

void	wall_render(t_ray *ray, t_text *text, t_game *game, int screen_x)
{
	int		y;
	float	factor;

	y = ray->d_start - 1;
	while (++y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tx_pos % (text->height - 1);
		ray->tx_pos += ray->step;
		ray->pixel = (char *)text->data + (ray->tex_y * text->size_line
				+ ray->tex_x * (text->bpp / 8));
		factor = 1.0f / (1.0f + ray->perp_wall_dist * 0.1f) + 0.2f;
		if (ray->side == 0)
			factor *= 0.8f;
		ray->color = dim_color(*(int *)ray->pixel, factor);
		put_pixel(screen_x, y, ray->color, game);
	}
}

void	floor_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = ray->draw_end - 1;
	while (++y < HEIGHT)
		put_pixel(screen_x, y, game->color_f, game);
}

void	ceiling_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = -1;
	while (++y < ray->d_start)
		put_pixel(screen_x, y, game->color_c, game);
}

void	vertical_texture(t_ray *ray, t_text *text)
{
	ray->step = 1.0f * text->height / ray->l_height;
	ray->tx_pos = (ray->d_start - HEIGHT / 2 + ray->l_height / 2)
		* ray->step;
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
