/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_texture_line(char *line, t_game *game, t_list **map_lines,
		int *map_started)
{
	if (*map_started)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Texture line after map started");
	}
	parse_texture(line, game);
}

static void	handle_color_line(char *line, t_game *game, t_list **map_lines,
		int *map_started)
{
	if (*map_started)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Color line after map started");
	}
	parse_color(line, game);
}

static void	handle_empty_line(t_game *game, t_list **map_lines,
		int *map_started)
{
	if (*map_started)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Invalid empty line in map");
	}
}

void	process_line(char *line, t_game *game, t_list **map_lines,
		int *map_started)
{
	if (is_empty_line(line))
	{
		handle_empty_line(game, map_lines, map_started);
		return ;
	}
	else if (is_texture_line(line))
	{
		handle_texture_line(line, game, map_lines, map_started);
		return ;
	}
	else if (is_color_line(line))
	{
		handle_color_line(line, game, map_lines, map_started);
		return ;
	}
	else if (is_map_line(line))
	{
		process_map_line(line, game, map_lines, map_started);
		return ;
	}
	else
		handle_line_error(game, map_lines, *map_started);
}
