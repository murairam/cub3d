/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_visibility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/31 17:43:06 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <math.h>

static bool	is_wall_blocking(t_game *game, int map_x, int map_y)
{
	int	i;

	if (map_y < 0 || map_x < 0 || map_y >= game->map_height || !game->map[map_y]
		|| map_x >= (int)ft_strlen(game->map[map_y]))
		return (true);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == '2')
		return (true);
	if (game->map[map_y][map_x] == 'D')
	{
		i = 0;
		while (i < game->door_count)
		{
			if (game->doors[i].x == map_x && game->doors[i].y == map_y)
				return (game->doors[i].state == 0);
			i++;
		}
	}
	return (false);
}

static bool	check_line_of_sight(t_game *game, double dx, double dy,
		double distance)
{
	double	step_size;
	int		steps;
	int		i;

	steps = (int)(distance / 16.0);
	if (steps < 1)
		steps = 1;
	step_size = 1.0 / steps;
	i = 1;
	while (i < steps)
	{
		if (is_wall_blocking(game, (int)((game->player.x + dx * i * step_size)
				/ CUBE), (int)((game->player.y + dy * i * step_size) / CUBE)))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_close_to_player(double dx, double dy)
{
	double	distance_squared;

	distance_squared = dx * dx + dy * dy;
	return (distance_squared < 32.0 * 32.0);
}

static double	calculate_distance_when_needed(double dx, double dy)
{
	return (sqrt(dx * dx + dy * dy));
}

bool	is_chalk_visible(t_game *game, t_chalk_sprite *sprite)
{
	double	dx;
	double	dy;

	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	if (is_close_to_player(dx, dy))
		return (true);
	return (check_line_of_sight(game, dx, dy,
			calculate_distance_when_needed(dx, dy)));
}
