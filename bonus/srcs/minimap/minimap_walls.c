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
			return (COLOR_RED); // Changed from COLOR_YELLOW to COLOR_RED for closed doors
		}
		door_idx++;
	}
	return (COLOR_RED); // Changed default from COLOR_YELLOW to COLOR_RED
}

static int	get_tile_color(t_game *game, int map_x, int map_y)
{
	char	tile;

	// Check bounds
	if (map_y < 0 || map_y >= game->map_height || map_x < 0 || 
		map_x >= (int)ft_strlen(game->map[map_y]))
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

void	draw_minimap_walls(t_game *game)
{
	int		player_map_x;
	int		player_map_y;
	int		start_x;
	int		start_y;
	int		mini_x;
	int		mini_y;
	int		map_x;
	int		map_y;
	int		color;

	// Get player position in map coordinates
	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	
	// Calculate the top-left corner of the 25x18 view centered on player
	start_x = player_map_x - MINIMAP_TILES_X / 2;
	start_y = player_map_y - MINIMAP_TILES_Y / 2;
	
	// Draw the 25x18 grid
	mini_y = 0;
	while (mini_y < MINIMAP_TILES_Y)
	{
		mini_x = 0;
		while (mini_x < MINIMAP_TILES_X)
		{
			map_x = start_x + mini_x;
			map_y = start_y + mini_y;
			color = get_tile_color(game, map_x, map_y);
			draw_tile(game, mini_x * MINIMAP_SCALE, mini_y * MINIMAP_SCALE, color);
			mini_x++;
		}
		mini_y++;
	}
}
