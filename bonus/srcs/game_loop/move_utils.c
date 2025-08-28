#include "cub3d_bonus.h"

static bool	check_tile_collision(t_game *game, int map_x, int map_y)
{
	char	tile;
	int		i;

	if (map_y < 0 || map_x < 0 || map_y >= game->map_height
		|| !game->map[map_y])
		return (true);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (true);
	tile = game->map[map_y][map_x];
	if (tile == '1' || tile == 'M' || tile == '2')
		return (true);
	if (tile != 'D')
		return (false);
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == map_x && game->doors[i].y == map_y)
			return (game->doors[i].state == DOOR_CLOSED);
		i++;
	}
	return (true);
}

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

static void	perform_move(t_game *game, float x_offset, float y_offset)
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

void	move_player_keys(t_player *player, t_game *game)
{
	float	cos_angle;
	float	sin_angle;
	int		speed;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	speed = 3;
	if (player->key_run)
		speed = 6;
	if (player->key_up)
		perform_move(game, cos_angle * speed, sin_angle * speed);
	if (player->key_down)
		perform_move(game, -cos_angle * speed, -sin_angle * speed);
	if (player->key_left)
		perform_move(game, sin_angle * speed, -cos_angle * speed);
	if (player->key_right)
		perform_move(game, -sin_angle * speed, cos_angle * speed);
}
