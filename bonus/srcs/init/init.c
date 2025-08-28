#include "cub3d_bonus.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->color_c = -1;
	game->color_f = -1;
	game->fd = 0;
	game->map = NULL;
	game->north.name = NULL;
	game->south.name = NULL;
	game->east.name = NULL;
	game->west.name = NULL;
	game->door.name = NULL;
	game->sprite_count = 0;
	game->door_count = 0;
	game->spawn_x = 0;
	game->spawn_y = 0;
	game->orientation = 0;
	game->fov = PI/3;
	game->stop = 0;
	game->darken_factor = 1;
	game->random_flag = 0;
	// if condition to check whether the mutex worked then cascade if it didnt :'(
	pthread_mutex_init(&game->darken_lock, NULL);
}
