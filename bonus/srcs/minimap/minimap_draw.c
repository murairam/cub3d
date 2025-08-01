#include "cub3d_bonus.h"

void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->minimap.width || y < 0 || y >= game->minimap.height)
		return ;
	
	dst = game->minimap.data + (y * game->minimap.size_line + x * (game->minimap.bpp / 8));
	*(unsigned int *)dst = color;
}

static void	composite_minimap_to_main(t_game *game)
{
	int		x, y;
	char	*minimap_pixel;
	char	*screen_pixel;
	unsigned int	minimap_color;
	unsigned int	screen_color;
	float	alpha = 0.7f; // 70% opacity

	y = 0;
	while (y < game->minimap.height && y < HEIGHT)
	{
		x = 0;
		while (x < game->minimap.width && x < WIDTH)
		{
			// Get minimap pixel
			minimap_pixel = game->minimap.data + (y * game->minimap.size_line + x * (game->minimap.bpp / 8));
			minimap_color = *(unsigned int *)minimap_pixel;
			
			// Get screen pixel at the same position in main image
			screen_pixel = game->data + (y * game->size_line + x * (game->bpp / 8));
			screen_color = *(unsigned int *)screen_pixel;
			
			// Skip black pixels (transparent areas)
			if (minimap_color != 0x000000)
			{
				// Blend colors
				unsigned int mr = (minimap_color >> 16) & 0xFF;
				unsigned int mg = (minimap_color >> 8) & 0xFF;
				unsigned int mb = minimap_color & 0xFF;
				
				unsigned int sr = (screen_color >> 16) & 0xFF;
				unsigned int sg = (screen_color >> 8) & 0xFF;
				unsigned int sb = screen_color & 0xFF;
				
				unsigned int br = (unsigned int)((1.0f - alpha) * sr + alpha * mr);
				unsigned int bg = (unsigned int)((1.0f - alpha) * sg + alpha * mg);
				unsigned int bb = (unsigned int)((1.0f - alpha) * sb + alpha * mb);
				
				unsigned int blended_color = (br << 16) | (bg << 8) | bb;
				*(unsigned int *)screen_pixel = blended_color;
			}
			x++;
		}
		y++;
	}
}

static void	clear_minimap_properly(t_game *game)
{
	char			*dst;
	int				y;
	int				x;
	unsigned int	border_color;
	unsigned int	bg_color;

	border_color = 0x4C4C4C; // Subtle gray border (30% white)
	bg_color = 0x000000; // Black background
	
	y = 0;
	while (y < game->minimap.height)
	{
		x = 0;
		while (x < game->minimap.width)
		{
			dst = game->minimap.data + (y * game->minimap.size_line + x * (game->minimap.bpp / 8));
			
			// Draw border on edges
			if (x == 0 || x == game->minimap.width - 1 || 
				y == 0 || y == game->minimap.height - 1)
				*(unsigned int *)dst = border_color;
			else
				*(unsigned int *)dst = bg_color;
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	static int	last_map_x = -1;
	static int	last_map_y = -1;
	static double last_angle = -999.0;
	int			current_map_x;
	int			current_map_y;
	int			fixed_width;
	int			fixed_height;
	bool		need_full_redraw;

	if (!game->show_minimap)
		return ;
	
	fixed_width = MINIMAP_TILES_X * MINIMAP_SCALE;
	fixed_height = MINIMAP_TILES_Y * MINIMAP_SCALE;
	
	// Get current player map position
	current_map_x = (int)(game->player.x / CUBE);
	current_map_y = (int)(game->player.y / CUBE);
	
	// Create image if it doesn't exist
	if (!game->minimap.img)
	{
		recreate_minimap_image(game, fixed_width, fixed_height);
		if (!game->minimap.img)
			return ;
		// Force redraw on first creation
		last_map_x = -999;
		last_map_y = -999;
		last_angle = -999.0;
	}
	
	// Check if we need full redraw (position changed or significant angle change)
	need_full_redraw = (current_map_x != last_map_x || current_map_y != last_map_y || 
						fabs(game->player.angle - last_angle) > 0.05);
	
	// Only redraw when necessary
	if (need_full_redraw)
	{
		// Clear and redraw the entire minimap
		clear_minimap_properly(game);
		draw_minimap_walls(game);
		draw_minimap_player(game);
		
		// Update last position and angle
		last_map_x = current_map_x;
		last_map_y = current_map_y;
		last_angle = game->player.angle;
	}
	
	// Composite the minimap onto the main image with transparency
	composite_minimap_to_main(game);
}
