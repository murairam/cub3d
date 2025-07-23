/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:48:48 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/24 20:21:38 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_next_move(t_map *game, t_vars *vars)
{
	char	next;

	next = game->map[game->player_pos.x][game->player_pos.y];
	if (next != WALL && next != EXIT)
	{
		game->map[game->player_pos.x][game->player_pos.y] = PLAYER;
		game->map[game->game_pos.x][game->game_pos.y] = SPACE;
		game->moves++;
		ft_printf("move count: %d\n", game->moves);
	}
	else if (next == WALL || (next == EXIT
			&& game->colls_in_wallet != game->num_of_collectibles))
	{
		game->player_pos.x = game->game_pos.x;
		game->player_pos.y = game->game_pos.y;
	}
	if (next == COLLECTIBLE)
		game->colls_in_wallet++;
	else if (next == EXIT && game->colls_in_wallet == game->num_of_collectibles)
	{
		ft_printf("you won! good for you\n");
		end_game(vars);
	}
	return (0);
}

int	game_keycodes(int keycode, t_vars *vars)
{
	if (keycode == UP || keycode == A_UP)
		vars->map.player_pos.x--;
	else if (keycode == DOWN || keycode == A_DOWN)
		vars->map.player_pos.x++;
	else if (keycode == LEFT || keycode == A_LEFT)
		vars->map.player_pos.y--;
	else if (keycode == RIGHT || keycode == A_RIGHT)
		vars->map.player_pos.y++;
	else if (keycode == ESC)
		end_game(vars);
	else
		return (0);
	return (1);
}

int	i_pressed_a_key(int keycode, t_vars *vars)
{
	vars->map.game_pos.x = vars->map.player_pos.x;
	vars->map.game_pos.y = vars->map.player_pos.y;
	if (!game_keycodes(keycode, vars))
		return (0);
	check_next_move(&vars->map, vars);
	return (0);
}
