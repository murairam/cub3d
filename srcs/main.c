#include "cub3d.h"

static int	valid_argc(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <maps/map.cub>\n", "cub3d");
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
		ft_free_game(&game);
		return (1);
	}
	game_loop(&game);
	ft_free_game(&game);
	return (0);
}
