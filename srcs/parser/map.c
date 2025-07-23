#include "cub3d.h"

static int	validate_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\n' || c == '\r');
}

static void	validate_characters_and_count_players(char **map, int *player_count)
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
			if (!validate_map_char(map[i][j]))
			{
				ft_free_split(map);
				ft_exit_error("Invalid character in map");
			}
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				(*player_count)++;
			j++;
		}
		i++;
	}
}

static void	validate_map_content(char **map)
{
	int	player_count;

	validate_characters_and_count_players(map, &player_count);
	if (player_count != 1)
	{
		ft_free_split(map);
		if (player_count == 0)
			ft_exit_error("No player found in map");
		else
			ft_exit_error("Multiple players found in map");
	}
	validate_map_boundaries(map);
}

void	parse_map(t_list *map_lines, t_game *game)
{
	char	**map;

	if (!map_lines)
		ft_exit_error("No map found");
	map = list_to_array(map_lines);
	if (!map)
		ft_exit_error("Memory allocation failed");
	validate_map_content(map);
	game->map = map;
}
