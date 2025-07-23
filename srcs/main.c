#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	ft_memset(&game, 0, sizeof(t_game));
	game.color_c = -1;
	game.color_f = -1;
	if (argc != 2)
		return (ft_printf("Usage: ./cub3D maps/map.cub\n"), 1);
	parse_file(argv[1], &game);
	printf("File parsed successfully!\n");
	printf("Map:\n");
	i = 0;
	while (game.map[i])
	{
		printf("%s\n", game.map[i]);
		i++;
	}
	return (0);
}
