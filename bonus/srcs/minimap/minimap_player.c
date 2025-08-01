#include "cub3d_bonus.h"

static void	draw_player_dot(t_game *game, int player_mini_x, int player_mini_y)
{
	int	i;
	int	j;
	int	player_size;

	player_size = 5; // Increased from 3 to 5 for bigger dot
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

static void	draw_player_fov_lines(t_game *game, int player_mini_x,
		int player_mini_y)
{
	int		steps;
	int		step;
	int		x, y;
	int		player_size;
	float	fov_half;
	float	left_angle, right_angle;

	player_size = 5; // Updated to match new player size
	steps = 12; // Longer lines for better visibility
	fov_half = (PI / 3) / 2; // Half of 60 degree FOV
	
	// Calculate left and right FOV angles
	left_angle = game->player.angle - fov_half;
	right_angle = game->player.angle + fov_half;
	
	// Draw left FOV line
	step = 0;
	while (step < steps)
	{
		x = player_mini_x + player_size / 2 + (int)(cos(left_angle) * step);
		y = player_mini_y + player_size / 2 + (int)(sin(left_angle) * step);
		put_pixel_minimap(game, x, y, COLOR_BLACK);
		step++;
	}
	
	// Draw right FOV line
	step = 0;
	while (step < steps)
	{
		x = player_mini_x + player_size / 2 + (int)(cos(right_angle) * step);
		y = player_mini_y + player_size / 2 + (int)(sin(right_angle) * step);
		put_pixel_minimap(game, x, y, COLOR_BLACK);
		step++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	player_mini_x;
	int	player_mini_y;
	int	player_size;
	int	center_tile_x;
	int	center_tile_y;

	player_size = 5; // Updated to match new player size
	
	// Player is always at the center of the 25x18 minimap
	center_tile_x = MINIMAP_TILES_X / 2;
	center_tile_y = MINIMAP_TILES_Y / 2;
	player_mini_x = center_tile_x * MINIMAP_SCALE + MINIMAP_SCALE / 2 - player_size / 2;
	player_mini_y = center_tile_y * MINIMAP_SCALE + MINIMAP_SCALE / 2 - player_size / 2;
	
	draw_player_dot(game, player_mini_x, player_mini_y);
	draw_player_fov_lines(game, player_mini_x, player_mini_y);
}
