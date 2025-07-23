#include "cub3d.h"

static int	rgb_component(char *s)
{
	int	n;

	n = ft_atoi(s);
	if (n < 0 || n > 255)
		ft_exit_error("RGB value must be between 0 and 255");
	return (n);
}

static int	parse_rgb(char *str)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			ft_free_split(rgb);
		ft_exit_error("RGB must have 3 values");
	}
	r = rgb_component(rgb[0]);
	g = rgb_component(rgb[1]);
	b = rgb_component(rgb[2]);
	color = (r << 16) | (g << 8) | b;
	ft_free_split(rgb);
	return (color);
}

static void	assign_color(int *target, int value, const char *label)
{
	(void)label;
	if (*target != -1)
		ft_exit_error("Duplicate color");
	*target = value;
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
		ft_exit_error("Invalid color format");
	}
	color = parse_rgb(split[1]);
	if (!ft_strncmp(split[0], "F", 1) && ft_strlen(split[0]) == 1)
		assign_color(&game->color_f, color, "F");
	else if (!ft_strncmp(split[0], "C", 1) && ft_strlen(split[0]) == 1)
		assign_color(&game->color_c, color, "C");
	else
	{
		ft_free_split(split);
		ft_exit_error("Unknown color identifier");
	}
	printf("Color %s set to %d\n", split[0], color);
	ft_free_split(split);
}
