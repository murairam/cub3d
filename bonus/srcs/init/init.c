#include "cub3d_bonus.h"

static int	init_game_utils(t_game *game)
{
	game->sprite_count = 0;
	game->door_count = 0;
	game->spawn_x = 0;
	game->spawn_y = 0;
	game->orientation = 0;
	game->fov = PI / 3;
	game->stop = 0;
	game->darken_factor = 1;
	game->print_flag = 0;
	game->random_flag = 0;
	game->minimap_toggle = false;
	return (1);
}

int	init_game(t_game *game)
{
	if (!ft_memset(game, 0, sizeof(t_game)))
	{
		ft_printf_fd(2, "Error: Game memory alloc failed\n");
		return (0);
	}
	if (pthread_mutex_init(&game->darken_lock, NULL) != 0)
	{
		ft_printf_fd(2, "Error: Mutex init failed\n");
		return (0);
	}
	game->map = NULL;
	game->north.name = NULL;
	game->south.name = NULL;
	game->east.name = NULL;
	game->west.name = NULL;
	game->door.name = NULL;
	game->color_c = -1;
	game->color_f = -1;
	game->fd = 0;
	game->ray_table.initialized = false;
	init_game_utils(game);
	return (1);
}
