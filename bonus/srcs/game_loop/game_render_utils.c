#include "cub3d_bonus.h"

static void	render_pixel_transparency(t_game *game, t_text *src,
		int indices[2])
{
	int				*dest_data;
	int				*src_data;
	unsigned int	color;

	dest_data = (int *)(game->data);
	src_data = (int *)(src->data);
	color = (unsigned int)src_data[indices[0]];
	if (color != 0 && color != 0xFF000000)
		dest_data[indices[1]] = src_data[indices[0]];
}

void	draw_image_with_transparency(t_game *game, t_text *src, int x, int y)
{
	int	coords[2];
	int	indices[2];

	if (!src || !src->data || !game || !game->data)
		return ;
	coords[0] = -1;
	while (++coords[0] < src->height)
	{
		if (y + coords[0] < 0 || y + coords[0] >= HEIGHT)
			continue ;
		coords[1] = -1;
		while (++coords[1] < src->width)
		{
			if (x + coords[1] < 0 || x + coords[1] >= WIDTH)
				continue ;
			indices[0] = (coords[0] * (src->size_line / 4)) + (src->width - 1
					- coords[1]);
			indices[1] = (y + coords[0]) * (game->size_line / 4) + (x
					+ coords[1]);
			render_pixel_transparency(game, src, indices);
		}
	}
}
