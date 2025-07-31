#include "cub3d_bonus.h"

void	init_parsing(const char *filename, t_game *game)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0 \
	|| ft_strlen(extension) != 4)
		ft_exit_error("File must have .cub extension");
	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		ft_exit_error("Failed to open file");
}

void	finalize_parsing(t_game *game, t_list *map_lines)
{
	close(game->fd);
	game->fd = 0;
	if (!game->north.name || !game->south.name || !game->west.name
		|| !game->east.name)
	{
		if (map_lines)
			ft_lstclear(&map_lines, free);
		ft_exit_error_with_cleanup(game, "Missing texture");
	}
	if (game->color_f == -1 || game->color_c == -1)
	{
		if (map_lines)
			ft_lstclear(&map_lines, free);
		ft_exit_error_with_cleanup(game, "Missing color");
	}
	parse_map(&map_lines, game);
	ft_lstclear(&map_lines, free);
}

void	handle_line_error(t_game *game, t_list **map_lines, int map_started)
{
	if (map_lines && *map_lines)
		ft_lstclear(map_lines, free);
	if (map_started)
		ft_exit_error_with_cleanup(game, "Invalid line after map started");
	else
		ft_exit_error_with_cleanup(game, "Invalid line");
}

void	process_map_line(char *line, t_game *game, t_list **map_lines,
		int *map_started)
{
	char	*line_copy;
	t_list	*new_node;

	line_copy = ft_strdup(line);
	if (!line_copy)
	{
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Memory allocation failed");
	}
	new_node = ft_lstnew(line_copy);
	if (!new_node)
	{
		free(line_copy);
		if (map_lines && *map_lines)
			ft_lstclear(map_lines, free);
		ft_exit_error_with_cleanup(game, "Memory allocation failed");
	}
	*map_started = 1;
	ft_lstadd_back(map_lines, new_node);
}
