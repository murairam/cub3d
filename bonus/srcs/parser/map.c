#include "cub3d_bonus.h"

void	validate_content(char **map, t_game *game, t_list **map_lines)
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
	// validate_door_consistency(game, map, map_lines);
	// validate_door_texture_file(game, map_lines);
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
	get_map_dimensions(map, game);
	fetch_player_cords(map, game);
	if (store_doors(map, game) == -1)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Memory allocation failed for doors");
	}
}
