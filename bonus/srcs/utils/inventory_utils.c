/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:05 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:35:06 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	chalk_count_in_inventory(t_game *game)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < game->item_count)
	{
		if (ft_strncmp(game->inventory[i], "Chalk", 5) == 0)
			count++;
	}
	return (count);
}

void	add_to_inv(t_game *game, char *item)
{
	if (game->item_count < MAX_ITEM)
		game->inventory[game->item_count++] = item;
}
