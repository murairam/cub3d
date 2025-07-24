#include "cub3d.h"

static char	**split_and_validate_rgb(char *str, char **outer_split, char *line,
	t_game *game)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_exit_error_with_cleanup_split_and_line(game, rgb, outer_split,
			line, "RGB must have 3 values");
	}
	return (rgb);
}

static void	validate_rgb_component(int value, char **rgb, char **outer_split,
	char *line, t_game *game)
{
	if (value < 0 || value > 255)
	{
		ft_exit_error_with_cleanup_split_and_line(game, rgb, outer_split,
			line, "RGB value must be between 0 and 255");
	}
}

static int	parse_rgb(char *str, char **outer_split, char *line, t_game *game)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	rgb = split_and_validate_rgb(str, outer_split, line, game);
	r = ft_atoi(rgb[0]);
	validate_rgb_component(r, rgb, outer_split, line, game);
	g = ft_atoi(rgb[1]);
	validate_rgb_component(g, rgb, outer_split, line, game);
	b = ft_atoi(rgb[2]);
	validate_rgb_component(b, rgb, outer_split, line, game);
	color = (r << 16) | (g << 8) | b;
	ft_free_split(rgb);
	return (color);
}

static void	process_color_assignment(char **split, int color, char *line,
	t_game *game)
{
	if (!ft_strncmp(split[0], "F", 1) && ft_strlen(split[0]) == 1)
	{
		if (game->color_f != -1)
			ft_exit_error_with_cleanup_split_and_line(game, split, NULL,
				line, "Duplicate color");
		game->color_f = color;
	}
	else if (!ft_strncmp(split[0], "C", 1) && ft_strlen(split[0]) == 1)
	{
		if (game->color_c != -1)
			ft_exit_error_with_cleanup_split_and_line(game, split, NULL,
				line, "Duplicate color");
		game->color_c = color;
	}
	else
	{
		ft_exit_error_with_cleanup_split_and_line(game, split, NULL, line,
			"Unknown color identifier");
	}
}

void	parse_color(char *line, t_game *game)
{
	char	**split;
	int		color;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		ft_exit_error_with_cleanup_split_and_line(game, split, NULL, line,
			"Invalid color format");
	}
	color = parse_rgb(split[1], split, line, game);
	process_color_assignment(split, color, line, game);
	ft_free_split(split);
}
