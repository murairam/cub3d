#include "cub3d_bonus.h"

static int	is_valid_char(char c)
{
	return (ft_strchr("10NSEWDM \n\r", c) != NULL);
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

static void	handle_door_error(t_game *game, char **map, t_list **map_lines,
		bool has_texture)
{
	ft_free_split(map);
	if (map_lines && *map_lines)
		ft_lstclear(map_lines, free);
	if (has_texture)
		ft_exit_error_with_cleanup(game,
			"Door texture specified but no doors found on map");
	else
		ft_exit_error_with_cleanup(game,
			"Doors found on map but no door texture specified");
}

void	validate_door_consistency(t_game *game, char **map,
		t_list **map_lines)
{
	int		i;
	int		j;
	bool	has_doors;
	bool	has_texture;

	has_doors = false;
	has_texture = (game->door.name != NULL);
	i = -1;
	while (map && map[++i] && !has_doors)
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'D')
				has_doors = true;
	}
	if ((has_texture && !has_doors) || (!has_texture && has_doors))
		handle_door_error(game, map, map_lines, has_texture);
}

void	validate_door_texture_file(t_game *game, t_list **map_lines)
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
