#include "cub3d_bonus.h"

int	is_map_line(char *line)
{
	bool	has_map_char;

	has_map_char = false;
	if (!line || !*line)
		return (0);
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W' || *line == 'D' || *line == 'M'
			|| *line == 'c' )
			has_map_char = true;
		else if (!(*line == ' ' || *line == '\n' || *line == '\r'))
			return (0);
		line++;
	}
	return (has_map_char);
}

int	is_color_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "DR ", 3) == 0);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
