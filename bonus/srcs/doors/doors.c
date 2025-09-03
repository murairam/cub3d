/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:12 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:37:13 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_door(char c)
{
	return (c == 'D' || c == 'X');
}

void	init_doors(t_game *game)
{
	int	i;

	if (game->door_count == 0)
		return ;
	i = 0;
	while (i < game->door_count)
	{
		game->doors[i].state = DOOR_CLOSED;
		i++;
	}
}
