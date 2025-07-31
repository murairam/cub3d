#include "cub3d_bonus.h"

void	wall_render(t_ray *ray, t_texture *text, t_game *game, int screen_x)
{
	int	y;

	vertical_texture(ray, text);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (text->height - 1);
		ray->tex_pos += ray->step;
		ray->color = text->data[text->height * ray->tex_y + ray->tex_x];
		put_pixel(screen_x, y, ray->color, game);
		y++;
	}
}

void	floor_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = ray->draw_end;
	while (y < HEIGHT)
	{
		put_pixel(screen_x, y, game->color_f, game);
		y++;
	}
}

void	ceiling_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(screen_x, y, game->color_c, game);
		y++;
	}
}

void	vertical_texture(t_ray *ray, t_texture *text)
{
	if (ray->perp_wall_dist <= 0)
		ray->perp_wall_dist = 1;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	ray->step = 1.0 * text->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}

void	texture_cord(t_ray *ray, t_player *player, t_texture *text)
{
	if (ray->side == 0)
		ray->wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor((double)ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)text->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = text->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = text->width - ray->tex_x - 1;
}
