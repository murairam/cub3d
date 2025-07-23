#include "cub3d.h"

int parse_file(const char *filename, t_game *game)
{
    game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		ft_error("open failed");
	// write_to_map(game);
	close(game->fd);

    return (1);
}