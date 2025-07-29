/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 13:16:25 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->minimap.width || y < 0 || y >= game->minimap.height)
		return ;
	dst = game->minimap.data + (y * game->minimap.size_line + x * (game->minimap.bpp / 8));
	*(unsigned int*)dst = color;
}

static void	get_map_dimensions(t_game *game, int *map_width, int *map_height)
{
	int	max_x;
	int	max_y;
	int	x;
	int	y;

	max_x = 0;
	max_y = 0;
	
	// Find the actual bounds of map content (walls and floors)
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			// Count any valid map character (walls, floors, player spawn, doors)
			if (game->map[y][x] == '1' || game->map[y][x] == '0' ||
				game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W' ||
				game->map[y][x] == 'D')
			{
				if (x > max_x)
					max_x = x;
				if (y > max_y)
					max_y = y;
			}
			x++;
		}
		y++;
	}
	
	// Add 1 because we want size, not just max index
	*map_width = max_x + 1;
	*map_height = max_y + 1;
}

void	draw_minimap(t_game *game)
{
	int	map_width;
	int	map_height;
	int	actual_width;
	int	actual_height;

	if (!game->show_minimap)
		return ;
	
	get_map_dimensions(game, &map_width, &map_height);
	
	// Calculate actual minimap dimensions
	actual_width = map_width * MINIMAP_SCALE;
	actual_height = map_height * MINIMAP_SCALE;
	
	// Only recreate image if dimensions changed
	if (!game->minimap.img || game->minimap.width != actual_width || 
		game->minimap.height != actual_height)
	{
		if (game->minimap.img)
			mlx_destroy_image(game->mlx, game->minimap.img);
		
		game->minimap.img = mlx_new_image(game->mlx, actual_width, actual_height);
		if (!game->minimap.img)
			return ;
		
		game->minimap.data = mlx_get_data_addr(game->minimap.img,
				&game->minimap.bpp, &game->minimap.size_line,
				&game->minimap.endian);
		if (!game->minimap.data)
			return ;
		
		game->minimap.width = actual_width;
		game->minimap.height = actual_height;
	}
	
	// Draw directly without clearing (since we're drawing the entire minimap)
	draw_minimap_walls(game, map_width, map_height);
	draw_minimap_player(game);
	
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
}

void	draw_minimap_walls(t_game *game, int map_width, int map_height)
{
	int		map_x;
	int		map_y;
	int		mini_x;
	int		mini_y;
	int		i;
	int		j;
	int		color;

	map_y = 0;
	while (map_y < map_height)
	{
		map_x = 0;
		while (map_x < map_width)
		{
			mini_x = map_x * MINIMAP_SCALE;
			mini_y = map_y * MINIMAP_SCALE;
			
			// Determine color based on map content
			if (game->map[map_y] && map_x < (int)ft_strlen(game->map[map_y]))
			{
				if (game->map[map_y][map_x] == '1')
					color = COLOR_WHITE;
				else if (game->map[map_y][map_x] == 'D')
				{
					// Check door state for color
					int door_idx = 0;
					color = COLOR_YELLOW; // Default door color
					while (door_idx < game->door_count)
					{
						if (game->doors[door_idx].x == map_x && 
							game->doors[door_idx].y == map_y)
						{
							if (game->doors[door_idx].state == DOOR_OPEN ||
								game->doors[door_idx].state == DOOR_OPENING)
								color = COLOR_GREEN; // Open door
							else
								color = COLOR_YELLOW; // Closed door
							break;
						}
						door_idx++;
					}
				}
				else if (game->map[map_y][map_x] == '0' || 
						game->map[map_y][map_x] == 'N' ||
						game->map[map_y][map_x] == 'S' ||
						game->map[map_y][map_x] == 'E' ||
						game->map[map_y][map_x] == 'W')
					color = COLOR_GRAY;
				else
					color = COLOR_BLACK;
			}
			else
			{
				color = COLOR_BLACK; // Fill areas beyond actual map content
			}
			
			// Draw a small square for each map cell
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
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int		player_mini_x;
	int		player_mini_y;
	int		i;
	int		j;
	int		player_size;

	player_size = 3;
	player_mini_x = (int)(game->player.x / CUBE * MINIMAP_SCALE) - player_size / 2;
	player_mini_y = (int)(game->player.y / CUBE * MINIMAP_SCALE) - player_size / 2;
	
	// Draw player as a small red square
	i = 0;
	while (i < player_size)
	{
		j = 0;
		while (j < player_size)
		{
			put_pixel_minimap(game, player_mini_x + j, player_mini_y + i, COLOR_RED);
			j++;
		}
		i++;
	}
	
	// Draw player direction line
	int steps = 8;
	for (int step = 0; step < steps; step++)
	{
		int x = player_mini_x + player_size / 2 + (int)(cos(game->player.angle) * step);
		int y = player_mini_y + player_size / 2 + (int)(sin(game->player.angle) * step);
		put_pixel_minimap(game, x, y, COLOR_YELLOW);
	}
}
