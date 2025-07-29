#include "cub3d.h"

static void	wall_render(t_ray *ray, t_texture *text, t_game *game, int screen_x)
{
	int	y;

	y = ray->drawStart - 1;
	while (++y < ray->drawEnd)
	{
		ray->texY = (int)ray->texPos % (text->height - 1);
		ray->texPos += ray->step;
		ray->pixel = (char *)text->data + (ray->texY * text->size_line
				+ ray->texX * (text->bpp / 8));
		ray->color = *(int *)ray->pixel;
		put_pixel(screen_x, y, ray->color, game);
	}
}

static void	floor_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = ray->drawEnd - 1;
	while (++y < HEIGHT)
		put_pixel(screen_x, y, game->color_f, game);
}

static void	ceiling_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = -1;
	while (++y < ray->drawStart)
		put_pixel(screen_x, y, game->color_c, game);
}

void	draw_line(t_player *player, t_game *game, float angle, int screen_x)
{
	t_ray		ray;
	t_texture	*text;

	ray_init(&ray, player, angle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	if (ray.side == 0 && ray.rayDirX > 0)
		text = &game->east;
	else if (ray.side == 0 && ray.rayDirX < 0)
		text = &game->west;
	else if (ray.side == 1 && ray.rayDirY > 0)
		text = &game->south;
	else
		text = &game->north;
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screen_x);
	wall_render(&ray, text, game, screen_x);
	floor_render(&ray, game, screen_x);
}
