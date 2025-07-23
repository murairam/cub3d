/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:03:51 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/30 16:24:10 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	is_rectangular(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.height)
	{
		if (ft_linelen(vars->map.map[i]) != vars->map.width)
			return (0);
		i++;
	}
	if (vars->map.height > MAX_HEIGHT || vars->map.width > MAX_WIDTH)
		return (0);
	return (1);
}

int	unknown_character(int c)
{
	if (c != COLLECTIBLE && c != PLAYER && c != EXIT && c != WALL \
												&& c != SPACE)
		return (1);
	return (0);
}

int	is_ber(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (path[len - 1] == 'r' && path[len - 2] == 'e' && path[len - 3] == 'b'
		&& path[len - 4] == '.')
		return (1);
	return (0);
}

int	is_components_valid(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.height)
	{
		j = 0;
		while (j < vars->map.width)
		{
			if (unknown_character(vars->map.map[i][j]))
				return (0);
			if (vars->map.map[i][j] == PLAYER)
				vars->map.num_of_players++;
			if (vars->map.map[i][j] == COLLECTIBLE)
				vars->map.num_of_collectibles++;
			if (vars->map.map[i][j] == EXIT)
				vars->map.num_of_exits++;
			j++;
		}
		i++;
	}
	if (vars->map.num_of_players == 1 && vars->map.num_of_exits == 1
		&& vars->map.num_of_collectibles > 0)
		return (1);
	return (0);
}

int	is_map_walled(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.width)
	{
		if (vars->map.map[0][i] != WALL || vars->map.map[vars->map.height
			- 1][i] != WALL)
			return (0);
		i++;
	}
	i = 0;
	while (i < vars->map.height)
	{
		if (vars->map.map[i][0] != WALL || vars->map.map[i][vars->map.width
			- 1] != WALL)
			return (0);
		i++;
	}
	return (1);
}
