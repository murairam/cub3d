#include "cub3d_bonus.h"

static t_door	*find_door_at_position(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

static bool	is_player_near_door(t_game *game, int door_x, int door_y)
{
	int	player_map_x;
	int	player_map_y;
	int	distance_x;
	int	distance_y;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	distance_x = abs(player_map_x - door_x);
	distance_y = abs(player_map_y - door_y);
	return ((distance_x <= 1 && distance_y <= 1) && (distance_x
			+ distance_y <= 2));
}

static bool	is_player_on_door(t_game *game, int door_x, int door_y)
{
	int	player_map_x;
	int	player_map_y;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	return (player_map_x == door_x && player_map_y == door_y);
}

static void	check_door_interaction(t_game *game, int x, int y)
{
	t_door	*door;

	if (y >= 0 && x >= 0 && game->map[y] && game->map[y][x] == 'D')
	{
		door = find_door_at_position(game, x, y);
		if (door && is_player_near_door(game, x, y))
		{
			if (door->state == DOOR_CLOSED)
				door->state = DOOR_OPEN;
			else if (door->state == DOOR_OPEN)
			{
				if (!is_player_on_door(game, x, y))
					door->state = DOOR_CLOSED;
			}
		}
	}
}

void	interact_door(t_game *game)
{
	int	check_positions[4][2];
	int	player_map_x;
	int	player_map_y;
	int	i;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	check_positions[0][0] = player_map_x;
	check_positions[0][1] = player_map_y - 1;
	check_positions[1][0] = player_map_x;
	check_positions[1][1] = player_map_y + 1;
	check_positions[2][0] = player_map_x - 1;
	check_positions[2][1] = player_map_y;
	check_positions[3][0] = player_map_x + 1;
	check_positions[3][1] = player_map_y;
	i = 0;
	while (i < 4)
	{
		check_door_interaction(game, check_positions[i][0],
			check_positions[i][1]);
		i++;
	}
}
