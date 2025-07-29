#include "cub3d_bonus.h"

bool	is_door(char c)
{
	return (c == 'D');
}

void	init_doors(t_game *game)
{
	int	i;

	if (game->door_count == 0)
		return ;
	
	// Initialize all doors to closed state
	i = 0;
	while (i < game->door_count)
	{
		game->doors[i].state = DOOR_CLOSED;
		game->doors[i].animation_time = 0.0f;
		game->doors[i].open_amount = 0.0f;
		i++;
	}
}

void	update_doors(t_game *game)
{
	int		i;
	float	animation_speed;

	animation_speed = 0.05f; // Adjust for door opening/closing speed
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].state == DOOR_OPENING)
		{
			game->doors[i].open_amount += animation_speed;
			if (game->doors[i].open_amount >= 1.0f)
			{
				game->doors[i].open_amount = 1.0f;
				game->doors[i].state = DOOR_OPEN;
			}
		}
		else if (game->doors[i].state == DOOR_CLOSING)
		{
			game->doors[i].open_amount -= animation_speed;
			if (game->doors[i].open_amount <= 0.0f)
			{
				game->doors[i].open_amount = 0.0f;
				game->doors[i].state = DOOR_CLOSED;
			}
		}
		i++;
	}
}

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
	int		player_map_x;
	int		player_map_y;
	int		distance_x;
	int		distance_y;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	distance_x = abs(player_map_x - door_x);
	distance_y = abs(player_map_y - door_y);
	
	// Player must be adjacent to the door (distance 1 in at least one direction)
	return ((distance_x <= 1 && distance_y <= 1) && 
			(distance_x + distance_y <= 2));
}

void	interact_door(t_game *game)
{
	int		check_positions[4][2];
	int		player_map_x;
	int		player_map_y;
	int		i;
	t_door	*door;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	
	// Check positions around the player (front, back, left, right)
	check_positions[0][0] = player_map_x;     // front
	check_positions[0][1] = player_map_y - 1;
	check_positions[1][0] = player_map_x;     // back
	check_positions[1][1] = player_map_y + 1;
	check_positions[2][0] = player_map_x - 1; // left
	check_positions[2][1] = player_map_y;
	check_positions[3][0] = player_map_x + 1; // right
	check_positions[3][1] = player_map_y;
	
	i = 0;
	while (i < 4)
	{
		int x = check_positions[i][0];
		int y = check_positions[i][1];
		
		// Check if position is valid and contains a door
		if (y >= 0 && x >= 0 && game->map[y] && game->map[y][x] == 'D')
		{
			door = find_door_at_position(game, x, y);
			if (door && is_player_near_door(game, x, y))
			{
				// Toggle door state
				if (door->state == DOOR_CLOSED)
					door->state = DOOR_OPENING;
				else if (door->state == DOOR_OPEN)
					door->state = DOOR_CLOSING;
				return ; // Only interact with first door found
			}
		}
		i++;
	}
}
