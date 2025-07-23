/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:16:22 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/25 19:05:11 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_linelen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	error(char *msg)
{
	ft_printf("Error:\n%s\n", msg);
	exit(1);
}

void	ft_moves_to_win(t_vars *vars)
{
	char	*move_count;
	int		x;
	int		y;

	x = vars->map.width * SIZE / 2;
	y = vars->map.height * SIZE + (SIZE / 2) + 3;
	move_count = ft_itoa(vars->map.moves);
	mlx_string_put(vars->mlx, vars->win, x, y, 0xFF0000, move_count);
	free(move_count);
	move_count = NULL;
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

int	get_map_height(char *file)
{
	int		height;
	char	*line;
	int		fd;

	height = 0;
	if (!is_ber(file))
		error("Invalid map file");
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		height++;
		free(line);
		line = NULL;
	}
	close(fd);
	free(line);
	return (height);
}
