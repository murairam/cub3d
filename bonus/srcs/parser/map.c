#include "cub3d_bonus.h"

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
	store_doors(map, game);
}
