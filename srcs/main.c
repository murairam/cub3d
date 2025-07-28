#include "cub3d.h"

static void	print_game_state(t_game *game)
{
	int	i;

	printf("\n=== GAME STATE DEBUG ===\n");
	printf("Colors: F=%d, C=%d\n", game->color_f, game->color_c);
	printf("Textures: N=%s, S=%s, E=%s, W=%s\n", 
		game->north.name ? game->north.name : "NULL",
		game->south.name ? game->south.name : "NULL", 
		game->east.name ? game->east.name : "NULL",
		game->west.name ? game->west.name : "NULL");
	if (game->map)
	{
		printf("Map contents:\n");
		i = 0;
		while (game->map[i])
		{
			printf("  [%d]: %s", i, game->map[i]);
			i++;
		}
	}
	else
		printf("Map: NULL\n");
	printf("========================\n\n");
}

int	main(int argc, char **argv)
{
	t_game	game;

	printf("DEBUG: Starting cub3D parser...\n");
	ft_memset(&game, 0, sizeof(t_game));
	printf("DEBUG: Memory cleared with ft_memset\n");
	init_game(&game);
	if (argc != 2)
		return (ft_printf("Usage: ./cub3D maps/map.cub\n"), 1);
	printf("DEBUG: Starting to parse file: %s\n", argv[1]);
	parse_file(argv[1], &game);
	printf("DEBUG: File parsing completed successfully!\n");
	print_game_state(&game);
	printf("DEBUG: Cleaning up memory...\n");
	game_init(&game);
	ft_free_game(&game);
	printf("DEBUG: Memory cleanup completed.\n");
	return (0);
}
