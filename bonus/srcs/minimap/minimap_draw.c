#include "cub3d_bonus.h"

static void	check_redraw_needed(t_game *game, int *coords, double *last_angle)
{
	int		current_map_x;
	int		current_map_y;
	bool	need_redraw;

	current_map_x = (int)(game->player.x / CUBE);
	current_map_y = (int)(game->player.y / CUBE);
	need_redraw = (current_map_x != coords[0] || current_map_y != coords[1]
			|| fabs(game->player.angle - *last_angle) > 0.05);
	if (need_redraw)
	{
		clear_minimap_properly(game);
		draw_minimap_walls(game);
		draw_minimap_player(game);
		coords[0] = current_map_x;
		coords[1] = current_map_y;
		*last_angle = game->player.angle;
	}
}

static void	init_minimap_if_needed(t_game *game, int *coords,
		double *last_angle)
{
	int	fixed_width;
	int	fixed_height;

	if (!game->minimap.img)
	{
		fixed_width = MINIMAP_TILES_X * MINIMAP_SCALE;
		fixed_height = MINIMAP_TILES_Y * MINIMAP_SCALE;
		recreate_minimap_image(game, fixed_width, fixed_height);
		if (!game->minimap.img)
			return ;
		coords[0] = -999;
		coords[1] = -999;
		*last_angle = -999.0;
	}
}

void	draw_minimap(t_game *game)
{
	static int		coords[2] = {-1, -1};
	static double	last_angle = -999.0;

	if (!game->show_minimap)
		return ;
	init_minimap_if_needed(game, coords, &last_angle);
	check_redraw_needed(game, coords, &last_angle);
	composite_minimap_to_main(game);
}
