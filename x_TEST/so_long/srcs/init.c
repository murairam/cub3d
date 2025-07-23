/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:07:36 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/22 12:47:13 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// vaata ule kas on uldse koik oigesti
void	initialize_game(t_vars *vars, char *map)
{
	vars->path = map;
	vars->map.moves = 0;
	vars->map.exit = FALSE;
	vars->map.num_of_collectibles = 0;
	vars->map.num_of_exits = 0;
	vars->map.num_of_players = 0;
	vars->map.player_pos.x = 0;
	vars->map.player_pos.y = 0;
	vars->map.game_pos.x = 0;
	vars->map.game_pos.y = 0;
	vars->map.colls_in_wallet = 0;
	vars->map.width = 0;
	vars->map.height = get_map_height(map);
	vars->duped_map = NULL;
}

void	init_map(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.map = malloc(sizeof(char *) * (vars->map.height + 1));
	if (!vars->map.map)
		error("malloc failed");
	while (i <= vars->map.height)
	{
		vars->map.map[i] = NULL;
		i++;
	}
}

char	**duplicate_map(t_vars *vars)
{
	int		i;
	char	**line;

	i = 0;
	line = malloc(sizeof(char *) * (vars->map.height + 1));
	if (!line)
	{
		free_map(line);
		error("malloc failed");
	}
	while (i < vars->map.height)
	{
		line[i] = ft_strdup(vars->map.map[i]);
		if (!line[i])
			error("malloc failed");
		i++;
	}
	line[i] = NULL;
	return (line);
}
