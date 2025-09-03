/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:05 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:37:06 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_step_and_side_dist(t_ray *ray, t_player *player)
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

static bool	is_wall_or_closed_door_chalk(t_game *game, int map_x, int map_y)
{
	int		i;
	char	tile;

	i = 0;
	if (map_y < 0 || map_x < 0 || map_y >= game->map_height
		|| !game->map[map_y])
		return (true);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (true);
	tile = game->map[map_y][map_x];
	if (tile == 'M' || tile == '1' || tile == '2')
		return (true);
	if (tile != 'D' && tile != 'X')
		return (false);
	while (i < game->door_count)
	{
		if (game->doors[i].x == map_x && game->doors[i].y == map_y)
			return (game->doors[i].state == DOOR_CLOSED);
		i++;
	}
	return (true);
}

void	dda_finder_chalk(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		ray_handler(ray);
		if (is_wall_or_closed_door_chalk(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

void	ray_init_chalk(t_ray *ray, t_player *player, float ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)(player->x / CUBE);
	ray->map_y = (int)(player->y / CUBE);
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = BIG_FLOAT;
	else
		ray->delta_dist_x = fabsf(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = BIG_FLOAT;
	else
		ray->delta_dist_y = fabsf(1 / ray->ray_dir_y);
	calculate_step_and_side_dist(ray, player);
}

void	wall_tag(t_player *player, t_game *game)
{
	t_ray	ray;

	if (chalk_count_in_inventory(game) <= 0)
	{
		game->print_flag = NO_CHALK;
		return ;
	}
	ray_init_chalk(&ray, player, player->angle);
	dda_finder_chalk(&ray, game);
	if (ray.map_y >= 0 && ray.map_y < game->map_height && ray.map_x >= 0
		&& game->map[ray.map_y]
		&& ray.map_x < (int)ft_strlen(game->map[ray.map_y])
		&& game->map[ray.map_y][ray.map_x] == '1')
	{
		game->map[ray.map_y][ray.map_x] = '2';
		remove_from_inv(game, "Chalk");
		game->print_flag = HELP_CHALK;
	}
	else if (game->map[ray.map_y][ray.map_x] == '2')
	{
		game->print_flag = NO_PRINT;
	}
}
