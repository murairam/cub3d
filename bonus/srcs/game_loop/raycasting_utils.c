#include "cub3d_bonus.h"

static bool	is_wall_or_closed_door(t_game *game, int map_x, int map_y)
{
	char	tile;
	int		i;

	if (map_y < 0 || map_x < 0 || map_y >= game->map_height)
		return (true);
	if (!game->map[map_y] || map_x >= (int)ft_strlen(game->map[map_y]))
		return (true);
	tile = game->map[map_y][map_x];
	if (tile == '1')
		return (true);
	if (tile == 'D')
	{
		i = 0;
		while (i < game->door_count)
		{
			if (game->doors[i].x == map_x && game->doors[i].y == map_y)
			{
				return (game->doors[i].state == DOOR_CLOSED);
			}
			i++;
		}
		return (true);
	}
	return (false);
}

void	dda_finder(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall_or_closed_door(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

void	distance_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->x / CUBE + (1 - ray->step_x)
				/ 2.0f) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y / CUBE + (1 - ray->step_y)
				/ 2.0f) / ray->ray_dir_y;
	if (ray->perp_wall_dist < 0.1f)
		ray->perp_wall_dist = 0.1f;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	ray_init2(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x / CUBE - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - player->x / CUBE)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y / CUBE - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - player->y / CUBE)
			* ray->delta_dist_y;
	}
}

void	ray_init(t_ray *ray, t_player *player, float ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)(player->x / CUBE);
	ray->map_y = (int)(player->y / CUBE);
	ray->delta_dist_x = fabsf(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabsf(1 / ray->ray_dir_y);
	ray_init2(ray, player);
}
