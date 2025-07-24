#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_boundary_or_invalid(char c)
{
	return (ft_isspace(c) || c == '\0');
}

static int	is_out_of_bounds(char **map, int i, int j)
{
	return (i < 0 || map[i] == NULL || j < 0
		|| j >= (int)ft_strlen(map[i]));
}

static int	check_boundary_condition(char **map, int i, int j)
{
	return (is_out_of_bounds(map, i, j - 1)
		|| is_boundary_or_invalid(map[i][j - 1])
		|| is_out_of_bounds(map, i, j + 1)
		|| is_boundary_or_invalid(map[i][j + 1])
		|| is_out_of_bounds(map, i - 1, j)
		|| is_boundary_or_invalid(map[i - 1][j])
		|| is_out_of_bounds(map, i + 1, j)
		|| is_boundary_or_invalid(map[i + 1][j]));
}

void	validate_boundaries(char **map, t_game *game, t_list **map_lines)
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
				if (check_boundary_condition(map, i, j))
				{
					ft_free_split(map);
					if (map_lines && *map_lines)
						ft_lstclear(map_lines, free);
					ft_exit_error_with_cleanup(game,
						"Map not properly enclosed by walls");
				}
			}
			j++;
		}
		i++;
	}
}
