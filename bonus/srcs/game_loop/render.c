#include "cub3d_bonus.h"

static	t_text	*north_south_walls(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_y > 0 && game->map[ray->map_y][ray->map_x] == '1')
		return (&game->south);
	else if (ray->ray_dir_y > 0 && game->map[ray->map_y][ray->map_x] == '2')
		return (&game->south_chalk);
	else if (game->map[ray->map_y][ray->map_x] == '1')
		return (&game->north);
	else
		return (&game->north_chalk);
}

static	t_text	*east_west_walls(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x > 0 && game->map[ray->map_y][ray->map_x] == '1')
		return (&game->east);
	else if (ray->ray_dir_x > 0 && game->map[ray->map_y][ray->map_x] == '2')
		return (&game->east_chalk);
	else if (game->map[ray->map_y][ray->map_x] == '1')
		return (&game->west);
	else
		return (&game->west_chalk);
}

static t_text	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->map_y >= 0 && ray->map_y < game->map_height
		&& ray->map_x >= 0 && game->map[ray->map_y]
		&& ray->map_x < (int)ft_strlen(game->map[ray->map_y])
		&& game->map[ray->map_y][ray->map_x] == 'D')
		return (&game->door);
	if (ray->side == 0)
		return (east_west_walls(game, ray));
	else
		return (north_south_walls(game, ray));
}
void	draw_line_fast(t_player *player, t_game *game, t_ray_table *table,
		int screen_x)
{
	t_ray	ray;
	t_text	*text;
	float	ray_angle;

	ray_angle = player->angle + table->ray_angles[screen_x];
	ray_init(&ray, player, ray_angle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	if (game->map[ray.map_y][ray.map_x] == 'M')
	{
		reflection(&ray, game, screen_x);
		return ;
	}
	text = get_wall_texture(game, &ray);
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screen_x);
	wall_render(&ray, text, game, screen_x);
	floor_render(&ray, game, screen_x);
}

void	draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
{
	t_ray		ray;
	t_text		*text;

	ray_init(&ray, player, ray_angle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	if (game->map[ray.map_y][ray.map_x] == 'M')
	{
		reflection(&ray, game, screen_x);
		return ;
	}
	text = get_wall_texture(game, &ray);
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screen_x);
	wall_render(&ray, text, game, screen_x);
	floor_render(&ray, game, screen_x);
}
