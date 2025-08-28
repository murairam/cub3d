#include "cub3d_bonus.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	free(game->north.name);
	free(game->south.name);
	free(game->east.name);
	free(game->west.name);
	free(game->north_chalk.name);
	free(game->south_chalk.name);
	free(game->east_chalk.name);
	free(game->west_chalk.name);
	free(game->door.name);
	free(game->mirror.name);
	if (game->inventory)
		ft_free_split(game->inventory);
}

void	ft_free_game(t_game *game)
{
	char	*cleanup_line;

	if (!game)
		return ;
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
	pthread_join(game->thread, NULL);
	pthread_mutex_destroy(&game->darken_lock);
}

void	ft_exit_error_with_cleanup(t_game *game, const char *msg)
{
	ft_free_game(game);
	ft_exit_error(msg);
}

int	close_game(t_game *game)
{
	game->stop = 1;
	if (!game)
		exit(0);
	cleanup_chalk_sprites(game);
	ft_free_mlx(game);
	ft_free_bonus(game);
	ft_free_game(game);
	cleanup_game(game);
	
	exit(0);
	return (0);
}
