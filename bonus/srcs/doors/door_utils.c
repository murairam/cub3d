#include "cub3d_bonus.h"

static t_door	*find_door_atx_position(t_game *game, int x, int y)
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

static bool	is_player_on_door(t_game *game, int door_x, int door_y)
{
	int	player_map_x;
	int	player_map_y;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	return (player_map_x == door_x && player_map_y == door_y);
}

static void	check_exit_interaction(t_game *game, int x, int y)
{
	t_door	*door;

	if (y >= 0 && x >= 0 && y < game->map_height && x < game->map_width
		&& game->map[y][x] == 'X' && has_item(game, "Key") == 0)
	{
		door = find_door_atx_position(game, x, y);
		if (door && game->inventory)
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

static void	check_door_interaction(t_game *game, int x, int y)
{
	t_door	*door;

	if (y >= 0 && x >= 0 && y < game->map_height && x < game->map_width
		&& game->map[y][x] == 'D')
	{
		door = find_door_atx_position(game, x, y);
		if (door)
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
	int	player_map_x;
	int	player_map_y;
	int	x;
	int	y;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	y = player_map_y - 1;
	while (y <= player_map_y + 1)
	{
		x = player_map_x - 1;
		while (x <= player_map_x + 1)
		{
			if (x == player_map_x && y == player_map_y)
			{
				x++;
				continue ;
			}
			check_door_interaction(game, x, y);
			check_exit_interaction(game, x, y);
			x++;
		}
		y++;
	}
}
