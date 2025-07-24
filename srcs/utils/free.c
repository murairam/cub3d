#include "cub3d.h"

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
	if (game->map)
		ft_free_split(game->map);
	free(game->tex_n);
	free(game->tex_s);
	free(game->tex_e);
	free(game->tex_w);
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
