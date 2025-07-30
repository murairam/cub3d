#include "cub3d_bonus.h"

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		close_game(game);
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rot = true;
	if (keycode == RIGHT)
		player->right_rot = true;
	if (keycode == E)
		interact_door(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rot = false;
	if (keycode == RIGHT)
		player->right_rot = false;
	return (0);
}

bool	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	// Convert world coordinates to map coordinates
	map_x = (int)(x / CUBE);
	map_y = (int)(y / CUBE);
	
	// Check bounds
	if (map_y < 0 || map_x < 0)
		return (true);
	if (!game->map[map_y] || !game->map[map_y][map_x])
		return (true);
	
	// Check if it's a wall
	if (game->map[map_y][map_x] == '1')
		return (true);
	
	// Check if it's a closed door
	if (game->map[map_y][map_x] == 'D')
	{
		// Find the door at this position
		for (int i = 0; i < game->door_count; i++)
		{
			if (game->doors[i].x == map_x && game->doors[i].y == map_y)
			{
				// Door acts as wall if closed or closing
				return (game->doors[i].state == DOOR_CLOSED || 
						game->doors[i].state == DOOR_CLOSING);
			}
		}
		// Default to closed if door not found
		return (true);
	}
	
	return (false);
}

void	move_player_keys(t_player *player, float cos_angle, float sin_angle,
		int speed, t_game *game)
{
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->x + cos_angle * speed;
		new_y = player->y + sin_angle * speed;
		
		// Check X movement independently
		if (!is_wall(game, new_x, player->y))
			player->x = new_x;
		// Check Y movement independently
		if (!is_wall(game, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_down)
	{
		new_x = player->x - cos_angle * speed;
		new_y = player->y - sin_angle * speed;
		
		// Check X movement independently
		if (!is_wall(game, new_x, player->y))
			player->x = new_x;
		// Check Y movement independently
		if (!is_wall(game, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_left)
	{
		new_x = player->x + sin_angle * speed;
		new_y = player->y - cos_angle * speed;
		
		// Check X movement independently
		if (!is_wall(game, new_x, player->y))
			player->x = new_x;
		// Check Y movement independently
		if (!is_wall(game, player->x, new_y))
			player->y = new_y;
	}
	if (player->key_right)
	{
		new_x = player->x - sin_angle * speed;
		new_y = player->y + cos_angle * speed;
		
		// Check X movement independently
		if (!is_wall(game, new_x, player->y))
			player->x = new_x;
		// Check Y movement independently
		if (!is_wall(game, player->x, new_y))
			player->y = new_y;
	}
}

void	move_player(t_player *player, t_game *game)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 2;
	angle_speed = 0.03;
	if (player->left_rot)
		player->angle -= angle_speed;
	if (player->right_rot)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player_keys(player, cos_angle, sin_angle, speed, game);
}

int	mouse_move(int x, int y, t_game *game)
{
	float	mouse_sensitivity;
	int		delta_x;
	int		center_x;

	mouse_sensitivity = 0.00001f;
	center_x = WIDTH / 2;
	// Calculate mouse movement delta
	delta_x = x - center_x;
	
	// Apply rotation based on mouse movement
	if (delta_x != 0)
	{
		game->player.angle += delta_x * mouse_sensitivity;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		mlx_mouse_move(game->mlx, game->win, center_x, y);
	}
	
	// Update mouse position
	// game->mouse_x = x;
	// game->mouse_y = y;
	return (0);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)button;
	(void)x;
	(void)y;
	(void)game;
	// Mouse press not needed for panning mode
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)button;
	(void)x;
	(void)y;
	(void)game;
	// Mouse release not needed for panning mode
	return (0);
}
