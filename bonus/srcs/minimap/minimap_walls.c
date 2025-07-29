#include "cub3d_bonus.h"

static void	draw_tile(t_game *game, int mini_x, int mini_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel_minimap(game, mini_x + j, mini_y + i, color);
			j++;
		}
		i++;
	}
}

static int	get_door_color(t_game *game, int map_x, int map_y)
{
	int	door_idx;

	door_idx = 0;
	while (door_idx < game->door_count)
	{
		if (game->doors[door_idx].x == map_x
			&& game->doors[door_idx].y == map_y)
		{
			if (game->doors[door_idx].state == DOOR_OPEN)
				return (COLOR_GREEN);
			return (COLOR_YELLOW);
		}
		door_idx++;
	}
	return (COLOR_YELLOW);
}

static int	get_tile_color(t_game *game, int map_x, int map_y, int map_height)
{
	char	tile;

	if (map_y >= map_height || map_x >= (int)ft_strlen(game->map[map_y]))
		return (COLOR_BLACK);
	tile = game->map[map_y][map_x];
	if (tile == '1')
		return (COLOR_WHITE);
	if (tile == 'D')
		return (get_door_color(game, map_x, map_y));
	if (tile == '0' || ft_strchr("NSEW", tile))
		return (COLOR_GRAY);
	return (COLOR_BLACK);
}

void	draw_minimap_walls(t_game *game, int map_width, int map_height)
{
	int		map_x;
	int		map_y;
	int		color;

	map_y = 0;
	while (map_y < map_height)
	{
		map_x = 0;
		while (map_x < map_width)
		{
			color = get_tile_color(game, map_x, map_y, map_height);
			draw_tile(game, map_x * MINIMAP_SCALE, map_y * MINIMAP_SCALE,
				color);
			map_x++;
		}
		map_y++;
	}
}
