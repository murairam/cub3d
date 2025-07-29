/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 16:09:22 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	fetch_player_cords(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				game->spawn_x = x * CUBE;
				game->spawn_y = y * CUBE;
				game->orientation = map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	count_doors(char **map, t_game *game)
{
	int	i;
	int	j;

	game->door_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				game->door_count++;
			j++;
		}
		i++;
	}
}

static void	initialize_doors(char **map, t_game *game)
{
	int	i;
	int	j;
	int	door_index;

	door_index = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D')
			{
				game->doors[door_index].x = j;
				game->doors[door_index].y = i;
				game->doors[door_index].state = DOOR_CLOSED;
				door_index++;
			}
		}
	}
}

void	store_doors(char **map, t_game *game)
{
	count_doors(map, game);
	if (game->door_count == 0)
		return ;
	game->doors = ft_calloc(game->door_count, sizeof(t_door));
	if (!game->doors)
		ft_exit_error_with_cleanup(game, "Memory allocation failed for doors");
	initialize_doors(map, game);
}

void	get_map_dimensions(char **map, t_game *game)
{
	int	y;
	int	x;
	int	max_width;
	int	max_height;
	int	rightmost_wall;

	y = 0;
	max_width = 0;
	max_height = 0;
	while (map[y])
	{
		x = 0;
		rightmost_wall = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (map[y][x] == '1')
			{
				rightmost_wall = x;
				max_height = y;
			}
			x++;
		}
		if (rightmost_wall > max_width)
			max_width = rightmost_wall;
		y++;
	}
	game->map_height = max_height + 1;
	game->map_width = max_width + 1;
}
