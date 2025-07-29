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
