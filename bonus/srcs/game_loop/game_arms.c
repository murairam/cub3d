/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_arms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:16 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:37:20 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	render_left_arm(t_game *game)
{
	if (game->left_arm.img && game->left_arm.data)
	{
		game->left_arm.x = WIDTH - game->left_arm.width;
		game->left_arm.y = HEIGHT - game->left_arm.height
			+ (int)game->arm_offset + 10;
		draw_image_with_transparency(game, &game->left_arm, game->left_arm.x,
			game->left_arm.y);
	}
}

static void	render_right_arm(t_game *game)
{
	if (game->right_arm.img && game->right_arm.data)
	{
		game->right_arm.x = 0;
		game->right_arm.y = HEIGHT - game->right_arm.height
			- (int)game->arm_offset + 10;
		draw_image_with_transparency(game, &game->right_arm,
			game->right_arm.x, game->right_arm.y);
	}
}

void	render_game_arms(t_game *game)
{
	render_left_arm(game);
	render_right_arm(game);
}
