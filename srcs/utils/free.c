#include "cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_free_game(t_game *game)
{
	if (game->map)
		ft_free_split(game->map);
	free(game->tex_N);
	free(game->tex_S);
	free(game->tex_E);
	free(game->tex_W);
	if (game->fd > 0)
		close(game->fd);
}

void	ft_exit_error_with_cleanup(t_game *game, const char *msg)
{
	if (game)
		ft_free_game(game);
	ft_exit_error(msg);
}

void	ft_exit_error_with_cleanup_and_list(t_game *game, t_list **map_lines,
	const char *msg)
{
	if (map_lines)
		ft_lstclear(map_lines, free);
	if (game)
		ft_free_game(game);
	ft_exit_error(msg);
}
