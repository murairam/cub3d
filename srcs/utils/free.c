#include "cub3d.h"

static void	ft_free_mlx(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_free_game(t_game *game)
{
	char	*cleanup_line;

	if (!game)
		return ;
	printf("DEBUG: Cleaning up memory...\n");
	ft_free_mlx(game);
	free(game->north.name);
	free(game->south.name);
	free(game->east.name);
	free(game->west.name);
	if (game->map)
		ft_free_split(game->map);
	if (game->current_line)
		free(game->current_line);
	if (game->fd > 0)
	{
		close(game->fd);
		cleanup_line = get_next_line(game->fd);
		if (cleanup_line)
			free(cleanup_line);
	}
}

/* THE ONLY cleanup function you need! */
void	ft_exit_error_with_cleanup(t_game *game, const char *msg)
{
	ft_free_game(game);
	ft_exit_error(msg);
}

int	close_game(t_game *game)
{
	ft_free_game(game);
	exit(0);
	return (0);
}
