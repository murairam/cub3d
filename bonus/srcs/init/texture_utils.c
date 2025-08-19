#include "cub3d_bonus.h"

short	load_texture(t_game *game, t_text *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (ft_error("Failed to load texture file"), 1);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->data)
		return (ft_error("Failed to get texture image data"), 1);
	return (0);
}
