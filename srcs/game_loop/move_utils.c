/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:40:47 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:40:48 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y + sin_angle * speed) / CUBE][(int)player->x
		/ CUBE] != '1')
		player->y += sin_angle * speed;
	if (game->map[(int)player->y / CUBE][(int)(player->x + cos_angle * speed)
		/ CUBE] != '1')
		player->x += cos_angle * speed;
}

void	move_backward(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y - sin_angle * speed) / CUBE][(int)player->x
		/ CUBE] != '1')
		player->y -= sin_angle * speed;
	if (game->map[(int)player->y / CUBE][(int)(player->x - cos_angle * speed)
		/ CUBE] != '1')
		player->x -= cos_angle * speed;
}

void	move_left(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y - cos_angle * speed) / CUBE][(int)player->x
		/ CUBE] != '1')
		player->y -= cos_angle * speed;
	if (game->map[(int)player->y / CUBE][(int)(player->x + sin_angle * speed)
		/ CUBE] != '1')
		player->x += sin_angle * speed;
}

void	move_right(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y + cos_angle * speed) / CUBE][(int)player->x
		/ CUBE] != '1')
		player->y += cos_angle * speed;
	if (game->map[(int)player->y / CUBE][(int)(player->x - sin_angle * speed)
		/ CUBE] != '1')
		player->x -= sin_angle * speed;
}
