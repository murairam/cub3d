#include "cub3d_bonus.h"

void	ft_free_wall_textures(t_game *game)
{
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->north_chalk.img)
		mlx_destroy_image(game->mlx, game->north_chalk.img);
	if (game->south_chalk.img)
		mlx_destroy_image(game->mlx, game->south_chalk.img);
	if (game->east_chalk.img)
		mlx_destroy_image(game->mlx, game->east_chalk.img);
	if (game->west_chalk.img)
		mlx_destroy_image(game->mlx, game->west_chalk.img);
}
