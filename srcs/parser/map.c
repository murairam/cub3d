#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\n' || c == '\r');
}

static void	validate_chars_and_count(char **map, int *player_count,
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
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				(*player_count)++;
			j++;
		}
		i++;
	}
}

static void	validate_content(char **map, t_game *game, t_list **map_lines)
{
	int	player_count;

	validate_chars_and_count(map, &player_count, game, map_lines);
	if (player_count != 1)
	{
		ft_free_split(map);
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		if (player_count == 0)
			ft_exit_error_with_cleanup(game, "No player found in map");
		else
			ft_exit_error_with_cleanup(game, "Multiple players found in map");
	}
	validate_boundaries(map, game, map_lines);
}
static void	fetch_player_cords(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' ||
				map[y][x] == 'E' || map[y][x] == 'W')
			{
				game->spawn_x = x * CUBE;
				game->spawn_y = y * CUBE;
				game->orientation = map[y][x];
			}
			x++;
		}
		y++;
	}
}

void	parse_map(t_list **map_lines, t_game *game)
{
	char	**map;

	if (!*map_lines)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "No map found");
	}
	map = list_to_array(*map_lines);
	if (!map)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Memory allocation failed");
	}
	validate_content(map, game, map_lines);
	game->map = map;
	fetch_player_cords(map, game);
}
