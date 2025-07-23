/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:38 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/25 18:22:19 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		error("invalid input");
	initialize_game(&vars, argv[1]);
	parsing(&vars);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		error("mlx failed");
	vars.win = mlx_new_window(vars.mlx, (vars.map.width) * SIZE, \
					(vars.map.height + 1) * SIZE, NAME);
	if (!vars.win)
		return (free(vars.mlx), 1);
	draw_map(&vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, i_pressed_a_key, &vars);
	mlx_hook(vars.win, DestroyNotify, ButtonPressMask, end_game, &vars);
	mlx_loop_hook(vars.mlx, &render, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
