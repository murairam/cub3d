#include "cub3d_bonus.h"

short	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (printf("Error: failed to load %s\n", path), 1);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->data)
		return (printf("Error: failed to get data from %s\n", path), 1);
	return (0);
}
