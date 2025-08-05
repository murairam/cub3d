#include "cub3d_bonus.h"

#define RGB_MAX 255

static void	cleanup_and_exit(char **rgb, char **outer_split, t_game *game,
		const char *msg)
{
	if (rgb)
		ft_free_split(rgb);
	if (outer_split)
		ft_free_split(outer_split);
	ft_exit_error_with_cleanup(game, msg);
}

static int	parse_rgb(char *str, char **outer_split, t_game *game)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		cleanup_and_exit(rgb, outer_split, game, "RGB must have 3 values");
	if (!ft_isdigit(*rgb[0]) || !ft_isdigit(*rgb[1]) || !ft_isdigit(*rgb[2]))
		cleanup_and_exit(rgb, outer_split, game, "RGB values must be integers");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > RGB_MAX || g < 0 || g > RGB_MAX || b < 0 || b > RGB_MAX)
		cleanup_and_exit(rgb, outer_split, game,
			"RGB value must be between 0 and 255");
	ft_free_split(rgb);
	return ((r << 16) | (g << 8) | b);
}

static void	process_color_assignment(char **split, int color, t_game *game)
{
	if (!ft_strncmp(split[0], "F", 1) && ft_strlen(split[0]) == 1)
	{
		if (game->color_f != -1)
		{
			ft_free_split(split);
			ft_exit_error_with_cleanup(game, "Duplicate color");
		}
		game->color_f = color;
	}
	else if (!ft_strncmp(split[0], "C", 1) && ft_strlen(split[0]) == 1)
	{
		if (game->color_c != -1)
		{
			ft_free_split(split);
			ft_exit_error_with_cleanup(game, "Duplicate color");
		}
		game->color_c = color;
	}
	else
	{
		ft_free_split(split);
		ft_exit_error_with_cleanup(game, "Unknown color identifier");
	}
}

void	parse_color(char *line, t_game *game)
{
	char	**split;
	int		color;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		if (split)
			ft_free_split(split);
		ft_exit_error_with_cleanup(game, "Invalid color format");
	}
	color = parse_rgb(split[1], split, game);
	process_color_assignment(split, color, game);
	ft_free_split(split);
}
