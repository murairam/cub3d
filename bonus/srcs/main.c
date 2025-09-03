/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:25 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:35:26 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	valid_argc(int argc)
{
	if (argc != 2)
	{
		ft_printf_fd(2, "Error\nUsage: %s <maps/map.cub>\n", "cub3d");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!valid_argc(argc))
		return (1);
	init_game(&game);
	parse_file(argv[1], &game);
	if (game_init(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	game_loop(&game);
	cleanup_game(&game);
	return (0);
}
