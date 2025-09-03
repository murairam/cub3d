/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:38:59 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:39:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**get_texture_target(char *id, t_game *game)
{
	if (ft_strncmp(id, "NO", 2) == 0 && ft_strlen(id) == 2)
		return (&game->north.name);
	else if (ft_strncmp(id, "SO", 2) == 0 && ft_strlen(id) == 2)
		return (&game->south.name);
	else if (ft_strncmp(id, "WE", 2) == 0 && ft_strlen(id) == 2)
		return (&game->west.name);
	else if (ft_strncmp(id, "EA", 2) == 0 && ft_strlen(id) == 2)
		return (&game->east.name);
	else
		return (NULL);
}

static void	validate_texture_format(char **split, t_game *game)
{
	if (!split || !split[0] || !split[1] || split[2])
	{
		if (split)
			ft_free_split(split);
		ft_exit_error_with_cleanup(game, "Invalid texture line format");
	}
}

void	parse_texture(char *line, t_game *game)
{
	char	**split;
	char	*id;
	char	**target;

	split = ft_split(line, ' ');
	validate_texture_format(split, game);
	id = split[0];
	target = get_texture_target(id, game);
	if (!target)
	{
		ft_free_split(split);
		ft_exit_error_with_cleanup(game, "Unknown texture identifier");
	}
	if (*target)
	{
		ft_free_split(split);
		ft_exit_error_with_cleanup(game, "Duplicate texture");
	}
	*target = ft_strtrim(split[1], "\n");
	ft_free_split(split);
}
