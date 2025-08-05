#include "cub3d_bonus.h"

static void	apply_alpha_blend(unsigned int minimap_color,
		unsigned int screen_color, char *screen_pixel)
{
	unsigned int	rgb[6];

	rgb[0] = (minimap_color >> 16) & 0xFF;
	rgb[1] = (minimap_color >> 8) & 0xFF;
	rgb[2] = minimap_color & 0xFF;
	rgb[3] = (screen_color >> 16) & 0xFF;
	rgb[4] = (screen_color >> 8) & 0xFF;
	rgb[5] = screen_color & 0xFF;
	rgb[0] = (unsigned int)((1.0f - MINIMAP_ALPHA) * rgb[3]
			+ MINIMAP_ALPHA * rgb[0]);
	rgb[1] = (unsigned int)((1.0f - MINIMAP_ALPHA) * rgb[4]
			+ MINIMAP_ALPHA * rgb[1]);
	rgb[2] = (unsigned int)((1.0f - MINIMAP_ALPHA) * rgb[5]
			+ MINIMAP_ALPHA * rgb[2]);
	*(unsigned int *)screen_pixel = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->minimap.width || y < 0 || y >= game->minimap.height)
		return ;
	dst = game->minimap.data + (y * game->minimap.size_line + x
			* (game->minimap.bpp / 8));
	*(unsigned int *)dst = color;
}

void	blend_pixel_colors(t_game *game, int x, int y)
{
	char			*minimap_pixel;
	char			*screen_pixel;
	unsigned int	minimap_color;
	unsigned int	screen_color;

	minimap_pixel = game->minimap.data + (y * game->minimap.size_line
			+ x * (game->minimap.bpp / 8));
	minimap_color = *(unsigned int *)minimap_pixel;
	screen_pixel = game->data + (y * game->size_line + x * (game->bpp / 8));
	screen_color = *(unsigned int *)screen_pixel;
	if (minimap_color != 0x000000)
		apply_alpha_blend(minimap_color, screen_color, screen_pixel);
}
