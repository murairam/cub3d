/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/28 17:03:51 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_sprites(t_game *game)
{
	// TODO: Implement sprite initialization
	game->sprite_count = 0;
	game->sprite_list = NULL;
	game->sprite_list_count = 0;
}

void	sort_sprites(t_sprite *sprites, int count)
{
	// TODO: Implement sprite sorting by distance
	(void)sprites;
	(void)count;
}
