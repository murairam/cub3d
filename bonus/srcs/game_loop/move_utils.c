#include "cub3d_bonus.h"

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
