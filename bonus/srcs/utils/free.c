/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 16:09:20 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	free(game->north.name);
	free(game->south.name);
	free(game->east.name);
	free(game->west.name);
	free(game->door.name);
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

void	ft_exit_error_with_cleanup(t_game *game, const char *msg)
{
	ft_free_game(game);
	ft_exit_error(msg);
}

int	close_game(t_game *game)
{
	ft_free_mlx(game);
	ft_free_bonus(game);
	ft_free_game(game);
	exit(0);
	return (0);
}
