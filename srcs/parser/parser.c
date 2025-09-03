/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:39:06 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:39:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_file(const char *filename, t_game *game)
{
	char	*line;
	t_list	*map_lines;
	int		map_started;

	map_lines = NULL;
	map_started = 0;
	init_parsing(filename, game);
	line = get_next_line(game->fd);
	while (line)
	{
		game->current_line = line;
		process_line(line, game, &map_lines, &map_started);
		free(line);
		game->current_line = NULL;
		line = get_next_line(game->fd);
	}
	finalize_parsing(game, map_lines);
}
