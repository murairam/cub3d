/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_render3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 00:00:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <math.h>

void	render_chalks(t_game *game)
{
	int	i;

	if (!game->chalk_sprites || game->chalk_sprite_count == 0)
		return ;
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		if (game->chalk_sprites[i].visible && !game->chalk_sprites[i].collected)
		{
			if (is_in_fov(game, game->chalk_sprites[i].x,
					game->chalk_sprites[i].y)
				&& is_chalk_visible(game, &game->chalk_sprites[i]))
				render_chalk_sprite(game, &game->chalk_sprites[i]);
		}
		i++;
	}
}
