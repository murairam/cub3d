#include "cub3d_bonus.h"

static t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (game->map[ray->map_y][ray->map_x] == 'D')
		return (&game->door);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->east);
		return (&game->west);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->south);
		return (&game->north);
	}
}

void	draw_line(t_player *player, t_game *game, float rayAngle, int screenX)
{
	t_ray		ray;
	t_texture	*text;

	ray_init(&ray, player, rayAngle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	text = get_wall_texture(game, &ray);
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screenX);
	wall_render(&ray, text, game, screenX);
	floor_render(&ray, game, screenX);
}
