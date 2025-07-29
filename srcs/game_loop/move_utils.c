#include "cub3d.h"

void	move_forward(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y + sin_angle * speed)][(int)player->x] != '1')
		player->y += sin_angle * speed;
	if (game->map[(int)player->y][(int)(player->x + cos_angle * speed)] != '1')
		player->x += cos_angle * speed;
}

void	move_backward(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y - sin_angle * speed)][(int)player->x] != '1')
		player->y -= sin_angle * speed;
	if (game->map[(int)player->y][(int)(player->x - cos_angle * speed)] != '1')
		player->x -= cos_angle * speed;
}

void	move_left(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y - cos_angle * speed)][(int)player->x] != '1')
		player->y -= cos_angle * speed;
	if (game->map[(int)player->y][(int)(player->x + sin_angle * speed)] != '1')
		player->x += sin_angle * speed;
}

void	move_right(t_player *player, t_game *game, float cos_angle,
		float sin_angle)
{
	int	speed;

	speed = 2;
	if (game->map[(int)(player->y + cos_angle * speed)][(int)player->x] != '1')
		player->y += cos_angle * speed;
	if (game->map[(int)player->y][(int)(player->x - sin_angle * speed)] != '1')
		player->x -= sin_angle * speed;
}
