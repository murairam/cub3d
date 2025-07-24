/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:55:38 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/23 18:00:09 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	free_line(t_vars *vars, char *line)
{
	if (ft_strlen(line) > 0)
		free(line);
	free_map(vars->map.map);
	error("malloc fail");
}

// map array initialization
void	write_to_map(t_vars *vars)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	init_map(vars);
	while (1)
	{
		tmp = get_next_line(vars->fd);
		if (!tmp)
			break ;
		line = ft_strtrim(tmp, "\n");
		free(tmp);
		if (!line)
			free_line(vars, line);
		if (i < vars->map.height)
		{
			vars->map.map[i] = ft_strdup(line);
			if (!vars->map.map[i])
				free_line(vars, line);
			vars->map.width = (int)ft_strlen(line);
			free(line);
			i++;
		}
	}
}

int	parsing(t_vars *vars)
{
	vars->fd = open(vars->path, O_RDONLY);
	if (vars->fd < 0)
		error("open failed");
	write_to_map(vars);
	close(vars->fd);
	if (!is_rectangular(vars) || !is_components_valid(vars)
		|| !is_map_walled(vars) || !is_path_valid(vars))
	{
		free_map(vars->map.map);
		error("faulty map");
	}
	vars->map.colls_in_wallet = 0;
	return (1);
}
