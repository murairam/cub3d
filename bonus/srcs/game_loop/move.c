#include "cub3d_bonus.h"

static int	key_press_utils(int keycode, t_game *game, t_player *player)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == SPACE && game->stop != 1)
		interact_door(game);
	if (keycode == F && game->stop != 1)
		wall_tag(player, game);
	if (keycode == E && game->stop != 1)
		pick_up_item(player, game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		close_game(game);
	handle_movement_keys(keycode, player);
	handle_view_keys(keycode, player);
	handle_action_keys(keycode, game, player);
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
	if (keycode == F)
		player->key_f_pressed = false; 
	return (0);
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
