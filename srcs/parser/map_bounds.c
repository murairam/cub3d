#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	check_horizontal_bounds(char **map, int i, int j)
{
	if (j == 0 || map[i][j - 1] == ' ')
	{
		ft_free_split(map);
		ft_exit_error("Map not properly enclosed by walls");
	}
	if (map[i][j + 1] == ' ' || map[i][j + 1] == '\n' ||
		map[i][j + 1] == '\r' || map[i][j + 1] == '\0')
	{
		ft_free_split(map);
		ft_exit_error("Map not properly enclosed by walls");
	}
}

static void	check_vertical_bounds(char **map, int i, int j)
{
	if (i == 0)
	{
		ft_free_split(map);
		ft_exit_error("Map not properly enclosed by walls");
	}
	if (j >= (int)ft_strlen(map[i - 1]) || map[i - 1][j] == ' ' ||
		map[i - 1][j] == '\n' || map[i - 1][j] == '\r' ||
		map[i - 1][j] == '\0')
	{
		ft_free_split(map);
		ft_exit_error("Map not properly enclosed by walls");
	}
	if (map[i + 1] == NULL)
	{
		ft_free_split(map);
		ft_exit_error("Map not properly enclosed by walls");
	}
	if (j >= (int)ft_strlen(map[i + 1]) || map[i + 1][j] == ' ' ||
		map[i + 1][j] == '\n' || map[i + 1][j] == '\r' ||
		map[i + 1][j] == '\0')
	{
		ft_free_split(map);
		ft_exit_error("Map not properly enclosed by walls");
	}
}

void	validate_map_boundaries(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]))
			{
				check_horizontal_bounds(map, i, j);
				check_vertical_bounds(map, i, j);
			}
			j++;
		}
		i++;
	}
}
