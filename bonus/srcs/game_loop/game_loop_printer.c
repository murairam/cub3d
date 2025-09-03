/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:21 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:37:22 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	print_finder(t_game *game, t_player	*player)
{
	if (is_close_enough(game, player, 'c') == 0)
		return (PICK_CHALK);
	else if (is_close_enough(game, player, 'k') == 0)
		return (PICK_KEY);
	else
		return (NO_PRINT);
}

static void	print_executer(t_game *game, char *to_print)
{
	static int	counter = 100;

	mlx_string_put(game->mlx, game->win, WIDTH / 2,
		HEIGHT / 2, 0xFFFFFF, to_print);
	counter--;
	if (counter <= 0)
	{
		counter = 100;
		game->print_flag = NO_PRINT;
	}
}

void	print_handler(t_game *game, t_player *player)
{
	static int	delay = 50;

	if (game->print_flag == NO_CHALK)
		print_executer(game, "You need Chalk to do this");
	else
	{
		if (game->print_flag == PICK_CHALK)
			print_executer(game, "Press E to pick up this piece of chalk");
		else if (game->print_flag == PICK_KEY)
			print_executer(game, "Press E to pick up this key");
		else if (game->print_flag == HELP_CHALK)
		{
			--delay;
			if (delay <= 0)
				print_executer(game, "Press F to mark the wall");
		}
		else
		{
			game->print_flag = print_finder(game, player);
			delay = 50;
		}
	}
}
