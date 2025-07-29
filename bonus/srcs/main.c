/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	valid_argc(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map.cub>\n", "cub3d_bonus");
		return (0);
	}
	return (1);
}

static int	valid_file_extension(char *file)
{
	char	*extension;

	if (!file)
		return (0);
	extension = ft_strrchr(file, '.');
	if (!extension)
		return (ft_error("file has no extension"));
	if (ft_strncmp(extension, ".cub", 4) != 0)
		return (ft_error("file must have .cub extension"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!valid_argc(argc))
		return (1);
	if (!valid_file_extension(argv[1]))
		return (1);
	init_game(&game);
	printf("DEBUG: Starting cub3d bonus with file: %s\n", argv[1]);
	parse_file(argv[1], &game);
	printf("DEBUG: File parsed successfully, starting game...\n");
	if (game_init(&game))
	{
		ft_free_game(&game);
		return (1);
	}
	ft_free_game(&game);
	return (0);
}
