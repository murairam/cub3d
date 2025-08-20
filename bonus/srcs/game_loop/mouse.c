#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	float	mouse_sensitivity;

	mouse_sensitivity = 0.002;
	if (x != game->mouse_x)
	{
		game->player.angle += (x - game->mouse_x) * mouse_sensitivity;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
	}
	if (y != game->mouse_y)
    {
        game->player.pitch += (y - game->mouse_y) * mouse_sensitivity;
        if (game->player.pitch > MAX_PITCH)
            game->player.pitch = MAX_PITCH;
        if (game->player.pitch < -MAX_PITCH)
            game->player.pitch = -MAX_PITCH;
    }
	game->mouse_x = x;
	game->mouse_y = y;
	return (0);
}
