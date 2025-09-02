#include "cub3d_bonus.h"

static void	apply_mouse_movement(t_game *game, int delta_x, int delta_y)
{
	float	mouse_sensitivity;

	mouse_sensitivity = 0.002f;
	if (delta_x != 0)
	{
		game->player.angle += delta_x * mouse_sensitivity;
		while (game->player.angle >= 2 * PI)
			game->player.angle -= 2 * PI;
		while (game->player.angle < 0)
			game->player.angle += 2 * PI;
	}
	if (delta_y != 0)
	{
		game->player.pitch += delta_y * mouse_sensitivity;
		if (game->player.pitch > MAX_PITCH)
			game->player.pitch = MAX_PITCH;
		if (game->player.pitch < -MAX_PITCH)
			game->player.pitch = -MAX_PITCH;
	}
}

int	mouse_move(int x, int y, t_game *game)
{
	int	delta_x;
	int	delta_y;
	int	center_x;
	int	center_y;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	delta_x = x - game->mouse_x;
	delta_y = y - game->mouse_y;
	if (abs(delta_x) > 100 || abs(delta_y) > 100)
	{
		game->mouse_x = x;
		game->mouse_y = y;
		return (0);
	}
	apply_mouse_movement(game, delta_x, delta_y);
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	game->mouse_x = center_x;
	game->mouse_y = center_y;
	return (0);
}
