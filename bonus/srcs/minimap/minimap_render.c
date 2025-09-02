#include "cub3d_bonus.h"

static void	draw_border_background(t_game *game, int x, int y)
{
	char			*dst;
	unsigned int	border_color;
	unsigned int	bg_color;

	border_color = 0x4C4C4C;
	bg_color = 0x000000;
	dst = game->minimap.data + (y * game->minimap.size_line + x
			* (game->minimap.bpp / 8));
	if (x == 0 || x == game->minimap.width - 1 || y == 0
		|| y == game->minimap.height - 1)
		*(unsigned int *)dst = border_color;
	else
		*(unsigned int *)dst = bg_color;
}

void	clear_minimap_properly(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->minimap.height)
	{
		x = 0;
		while (x < game->minimap.width)
		{
			draw_border_background(game, x, y);
			x++;
		}
		y++;
	}
}

void	composite_minimap_to_main(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->minimap.height && y < HEIGHT)
	{
		x = 0;
		while (x < game->minimap.width && x < WIDTH)
		{
			blend_pixel_colors(game, x, y);
			x++;
		}
		y++;
	}
}

void	minimap_toggle(t_game *game)
{
	if (game->minimap_toggle == false)
		game->minimap_toggle = true;
	else
		game->minimap_toggle = false;
}