#include "cub3d_bonus.h"

static int	is_valid_char(char c)
{
	return (ft_strchr("10NSEWD \n\r", c) != NULL);
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
			if (ft_strchr("NSEW", map[i][j]))
				(*player_count)++;
			j++;
		}
		i++;
	}
}

static void	validate_door_consistency(t_game *game, char **map,
		t_list **map_lines)
{
	int		i;
	int		j;
	bool	has_doors_on_map;
	bool	has_door_texture;

	has_doors_on_map = false;
	has_door_texture = (game->door.name != NULL);
	if (map)
	{
		i = 0;
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				if (map[i][j] == 'D')
				{
					has_doors_on_map = true;
					break ;
				}
				j++;
			}
			if (has_doors_on_map)
				break ;
			i++;
		}
	}
	if (has_door_texture && !has_doors_on_map)
	{
		ft_free_split(map);
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game,
			"Door texture specified but no doors found on map");
	}
	if (!has_door_texture && has_doors_on_map)
	{
		ft_free_split(map);
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game,
			"Doors found on map but no door texture specified");
	}
}

static void	validate_door_texture_file(t_game *game, t_list **map_lines)
{
	int	fd;

	if (!game->door.name)
		return ;
	fd = open(game->door.name, O_RDONLY);
	if (fd == -1)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Door texture file cannot be opened");
	}
	close(fd);
}

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
    validate_door_consistency(game, map, map_lines);
	validate_door_texture_file(game, map_lines);
}
