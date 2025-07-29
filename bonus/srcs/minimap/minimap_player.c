#include "cub3d_bonus.h"

static void	draw_player_dot(t_game *game, int player_mini_x, int player_mini_y)
{
	int	i;
	int	j;
	int	player_size;

	player_size = 3;
	i = 0;
	while (i < player_size)
	{
		j = 0;
		while (j < player_size)
		{
			put_pixel_minimap(game, player_mini_x + j, player_mini_y + i,
				COLOR_RED);
			j++;
		}
		i++;
	}
}

static void	draw_player_direction(t_game *game, int player_mini_x,
		int player_mini_y)
{
	int	steps;
	int	step;
	int	x;
	int	y;
	int	player_size;

	player_size = 3;
	steps = 8;
	step = 0;
	while (step < steps)
	{
		x = player_mini_x + player_size / 2 + (int)(cos(game->player.angle)
				* step);
		y = player_mini_y + player_size / 2 + (int)(sin(game->player.angle)
				* step);
		put_pixel_minimap(game, x, y, COLOR_YELLOW);
		step++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	player_mini_x;
	int	player_mini_y;
	int	player_size;

	player_size = 3;
	player_mini_x = (int)(game->player.x / CUBE * MINIMAP_SCALE) - player_size
		/ 2;
	player_mini_y = (int)(game->player.y / CUBE * MINIMAP_SCALE) - player_size
		/ 2;
	draw_player_dot(game, player_mini_x, player_mini_y);
	draw_player_direction(game, player_mini_x, player_mini_y);
}
