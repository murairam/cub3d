#include "cub3d_bonus.h"

static int	is_valid_char(char c)
{
	return (ft_strchr("10NSEWDMXckm \n\r", c) != NULL);
}

void	validate_chars_and_count(char **map, int *player_count,
		t_game *game, t_list **map_lines)
{
	int	i;
	int	j;

	*player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
			{
				ft_free_split(map);
				if (map_lines && *map_lines)
					ft_lstclear(map_lines, free);
				ft_exit_error_with_cleanup(game, "Invalid character in map");
			}
			if (ft_strchr("NSEW", map[i][j]))
				(*player_count)++;
			j++;
		}
		i++;
	}
}

