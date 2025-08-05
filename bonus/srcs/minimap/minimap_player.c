#include "cub3d_bonus.h"

static void	draw_player_dot(t_game *game, int player_mini_x, int player_mini_y)
{
	int	i;
	int	j;
	int	player_size;

	player_size = 5;
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

static void	draw_fov_line(t_game *game, int player_mini_x, int player_mini_y,
		float angle)
{
	int	steps;
	int	step;
	int	player_size;
	int	x;
	int	y;

	player_size = 5;
	steps = 12;
	step = 0;
	while (step < steps)
	{
		x = player_mini_x + player_size / 2 + (int)(cos(angle) * step);
		y = player_mini_y + player_size / 2 + (int)(sin(angle) * step);
		put_pixel_minimap(game, x, y, COLOR_BLACK);
		step++;
	}
}

static void	draw_player_fov_lines(t_game *game, int player_mini_x,
		int player_mini_y)
{
	float	fov_half;
	float	left_angle;
	float	right_angle;

	fov_half = (PI / 3) / 2;
	left_angle = game->player.angle - fov_half;
	right_angle = game->player.angle + fov_half;
	draw_fov_line(game, player_mini_x, player_mini_y, left_angle);
	draw_fov_line(game, player_mini_x, player_mini_y, right_angle);
}

void	draw_minimap_player(t_game *game)
{
	int	player_mini_x;
	int	player_mini_y;
	int	player_size;
	int	center_tile_x;
	int	center_tile_y;

	player_size = 5;
	center_tile_x = MINIMAP_TILES_X / 2;
	center_tile_y = MINIMAP_TILES_Y / 2;
	player_mini_x = center_tile_x * MINIMAP_SCALE + MINIMAP_SCALE / 2
		- player_size / 2;
	player_mini_y = center_tile_y * MINIMAP_SCALE + MINIMAP_SCALE / 2
		- player_size / 2;
	draw_player_dot(game, player_mini_x, player_mini_y);
	draw_player_fov_lines(game, player_mini_x, player_mini_y);
}
