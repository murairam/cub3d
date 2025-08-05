#include "cub3d_bonus.h"

void	init_minimap(t_game *game)
{
	int	minimap_width;
	int	minimap_height;

	minimap_width = MINIMAP_TILES_X * MINIMAP_SCALE;
	minimap_height = MINIMAP_TILES_Y * MINIMAP_SCALE;
	game->minimap.width = minimap_width;
	game->minimap.height = minimap_height;
	game->minimap.img = mlx_new_image(game->mlx, minimap_width, minimap_height);
	if (!game->minimap.img)
		ft_exit_error_with_cleanup(game, "Failed to create minimap image");
	game->minimap.data = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bpp, &game->minimap.size_line,
			&game->minimap.endian);
	if (!game->minimap.data)
		ft_exit_error_with_cleanup(game, "Failed to get minimap data address");
	game->show_minimap = true;
}

void	recreate_minimap_image(t_game *game, int width, int height)
{
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	game->minimap.img = mlx_new_image(game->mlx, width, height);
	if (!game->minimap.img)
		return ;
	game->minimap.data = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bpp, &game->minimap.size_line,
			&game->minimap.endian);
	if (!game->minimap.data)
		return ;
	game->minimap.width = width;
	game->minimap.height = height;
}
