#include "cub3d.h"

void	init_game(t_game *game)
{
	printf("DEBUG: init_game() called\n");
	ft_memset(game, 0, sizeof(t_game));
	printf("DEBUG: ft_memset completed in init_game\n");
	game->color_c = -1;
	game->color_f = -1;
	printf("DEBUG: Colors initialized to F=%d, C=%d\n",
		game->color_f, game->color_c);
	game->fd = 0;
	game->map = NULL;
	game->tex_n = NULL;
	game->tex_s = NULL;
	game->tex_e = NULL;
	game->tex_w = NULL;
	printf("DEBUG: All pointers set to NULL\n");
}
