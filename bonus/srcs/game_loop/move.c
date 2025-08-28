#include "cub3d_bonus.h"

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		close_game(game);
	if (keycode == W && game->stop != 1)
		player->key_up = true;
	if (keycode == S && game->stop != 1)
		player->key_down = true;
	if (keycode == A && game->stop != 1)
		player->key_left = true;
	if (keycode == D && game->stop != 1)
		player->key_right = true;
	if (keycode == LEFT && game->stop != 1)
		player->left_rot = true;
	if (keycode == RIGHT && game->stop != 1)
		player->right_rot = true;
	if (keycode == UP && game->stop != 1)
		player->pitch_up = true;
	if (keycode == DOWN && game->stop != 1)
		player->pitch_down = true;
	if (keycode == SPACE && game->stop != 1)
		interact_door(game);
	if (keycode == F && game->stop != 1)
		wall_tag(player, game);
	if (keycode == E && game->stop != 1)
		pick_up_item(player, game);
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
	if (keycode == UP)
		player->pitch_up = false;
	if (keycode == DOWN)
		player->pitch_down = false;
	return (0);
}

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

void	move_player(t_player *player, t_game *game)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rot)
		player->angle -= angle_speed;
	if (player->right_rot)
		player->angle += angle_speed;
	if (player->pitch_up)
	{
		player->pitch -= angle_speed;
		if (player->pitch < -MAX_PITCH)
			player->pitch = -MAX_PITCH;
	}
	if (player->pitch_down)
	{
		player->pitch += angle_speed;
		if (player->pitch > MAX_PITCH)
			player->pitch = MAX_PITCH;
	}
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	move_player_keys(player, game);
}
