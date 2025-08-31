#include "cub3d_bonus.h"

bool	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / CUBE);
	map_y = (int)(y / CUBE);
	return (check_tile_collision(game, map_x, map_y));
}

bool	teleport_check(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / CUBE);
	map_y = (int)(y / CUBE);
	if (game->map[map_y][map_x] == '0' || game->map[map_y][map_x] == 'c' )
		return (false);
	else
		return (true);
}

void	perform_move(t_game *game, float x_offset, float y_offset)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = &game->player;
	new_x = player->x + x_offset;
	new_y = player->y + y_offset;
	if (!is_wall(game, new_x, player->y))
		player->x = new_x;
	if (!is_wall(game, player->x, new_y))
		player->y = new_y;
}
