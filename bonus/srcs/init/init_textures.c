/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/02 14:11:10 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"

short	wall_textures(t_game *game)
{
	if (load_texture(game, &game->north, game->north.name))
		return (1);
	if (load_texture(game, &game->south, game->south.name))
		return (1);
	if (load_texture(game, &game->east, game->east.name))
		return (1);
	if (load_texture(game, &game->west, game->west.name))
		return (1);
	if (load_texture(game, &game->north_chalk, TEX_CHALK_N))
		return (1);
	if (load_texture(game, &game->south_chalk, TEX_CHALK_S))
		return (1);
	if (load_texture(game, &game->east_chalk, TEX_CHALK_E))
		return (1);
	if (load_texture(game, &game->west_chalk, TEX_CHALK_W))
		return (1);
	if (load_texture(game, &game->left_arm, TEX_LEFT_ARM))
		return (1);
	if (load_texture(game, &game->right_arm, TEX_RIGHT_ARM))
		return (1);
	if (load_texture(game, &game->right_chalk, TEX_CHALK_R_ARM))
		return (1);
	return (0);
}

short	texture_init(t_game *game)
{
	if (wall_textures(game) == 1)
		return (1);
	if (load_texture(game, &game->mirror, TEX_MIRROR))
		return (1);
	if (load_texture(game, &game->exit, TEX_EXIT))
		return (1);
	if (load_texture(game, &game->char_mirror, TEX_CHAR_MIRROR))
		return (1);
	if (load_texture(game, &game->screen_over, TEX_GAME_OVER))
		return (1);
	if (load_texture(game, &game->screen_win, TEX_GAME_WIN))
		return (1);	
	if (load_texture(game, &game->door, TEX_DOOR))
		return (1);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
