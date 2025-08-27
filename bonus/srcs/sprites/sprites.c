/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_sprites(t_game *game)
{
	game->sprite_count = 0;
	game->sprite_list = NULL;
	game->sprite_list_count = 0;
}

void	sort_sprites(t_sprite *sprites, int count)
{
	(void)sprites;
	(void)count;
}
