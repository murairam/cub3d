#include "cub3d.h"

static char	**get_texture_target(char *id, t_game *game)
{
	if (ft_strncmp(id, "NO", 2) == 0 && ft_strlen(id) == 2)
		return (&game->tex_n);
	else if (ft_strncmp(id, "SO", 2) == 0 && ft_strlen(id) == 2)
		return (&game->tex_s);
	else if (ft_strncmp(id, "WE", 2) == 0 && ft_strlen(id) == 2)
		return (&game->tex_w);
	else if (ft_strncmp(id, "EA", 2) == 0 && ft_strlen(id) == 2)
		return (&game->tex_e);
	else
		return (NULL);
}

static void	validate_texture_format(char **split)
{
	if (!split || !split[0] || !split[1] || split[2])
	{
		if (split)
			ft_free_split(split);
		ft_exit_error("Invalid texture line format");
	}
}

void	parse_texture(char *line, t_game *game)
{
	char	**split;
	char	*id;
	char	**target;

	split = ft_split(line, ' ');
	validate_texture_format(split);
	id = split[0];
	target = get_texture_target(id, game);
	if (!target)
	{
		ft_free_split(split);
		ft_exit_error("Unknown texture identifier");
	}
	if (*target)
	{
		ft_free_split(split);
		ft_exit_error("Duplicate texture");
	}
	*target = ft_strdup(split[1]);
	printf("Texture %s set to %s\n", id, *target);
	ft_free_split(split);
}
