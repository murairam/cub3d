/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:32:18 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/23 17:58:24 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	floodfill(t_vars *vars, int x, int y)
{
	if (x < 0 || y < 0 || x >= vars->map.width || y >= vars->map.height \
		|| vars->duped_map[y][x] == WALL)
		return ;
	if (vars->duped_map[y][x] == COLLECTIBLE)
		vars->map.colls_in_wallet++;
	if (vars->duped_map[y][x] == EXIT)
	{
		vars->map.exit = TRUE;
		if (vars->map.num_of_collectibles == vars->map.colls_in_wallet)
			vars->duped_map[y][x] = WALL;
		return ;
	}
	if (vars->duped_map[y][x] == COLLECTIBLE || vars->duped_map[y][x] == SPACE)
		vars->duped_map[y][x] = WALL;
	floodfill(vars, x + 1, y);
	floodfill(vars, x - 1, y);
	floodfill(vars, x, y + 1);
	floodfill(vars, x, y - 1);
	return ;
}

void	position_player(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->map.map[i][j] == PLAYER)
			{
				vars->map.player_pos.x = i;
				vars->map.player_pos.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	is_path_valid(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	vars->duped_map = duplicate_map(vars);
	position_player(vars);
	floodfill(vars, vars->map.player_pos.y, vars->map.player_pos.x);
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (vars->duped_map[i][j] == COLLECTIBLE || vars->map.exit == FALSE)
				return (free_map(vars->duped_map), 0);
			j++;
		}
		i++;
	}
	free_map(vars->duped_map);
	vars->duped_map = NULL;
	return (1);
}
