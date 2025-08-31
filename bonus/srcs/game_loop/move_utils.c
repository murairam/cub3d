#include "cub3d_bonus.h"

bool	check_tile_collision(t_game *game, int map_x, int map_y)
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

void	handle_movement_keys(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
}

void	handle_view_keys(int keycode, t_player *player)
{
	if (keycode == LEFT)
		player->left_rot = true;
	if (keycode == RIGHT)
		player->right_rot = true;
	if (keycode == UP)
		player->pitch_up = true;
	if (keycode == DOWN)
		player->pitch_down = true;
}

void	handle_action_keys(int keycode, t_game *game, t_player *player)
{
	if (keycode == SPACE)
		interact_door(game);
	if (keycode == F && !player->key_f_pressed)
	{
		wall_tag(player, game);
		player->key_f_pressed = true;
	}
	if (keycode == E)
		pick_up_item(player, game);
}
