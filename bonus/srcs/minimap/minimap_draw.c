/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 15:09:11 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->minimap.width || y < 0 || y >= game->minimap.height)
		return ;
	dst = game->minimap.data + (y * game->minimap.size_line + x
			* (game->minimap.bpp / 8));
	*(unsigned int *)dst = color;
}

static void	get_map_dimensions(t_game *game, int *map_width, int *map_height)
{
	int	max_x;
	int	max_y;
	int	x;
	int	y;

	max_x = 0;
	max_y = 0;
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_strchr("01NSWED", game->map[y][x]))
			{
				if (x > max_x)
					max_x = x;
				if (y > max_y)
					max_y = y;
			}
		}
	}
	*map_width = max_x + 1;
	*map_height = max_y + 1;
}

static void	recreate_minimap_image(t_game *game, int width, int height)
{
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	game->minimap.img = mlx_new_image(game->mlx, width, height);
	if (!game->minimap.img)
		return ;
	game->minimap.data = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bpp, &game->minimap.size_line,
			&game->minimap.endian);
	if (!game->minimap.data)
		return ;
	game->minimap.width = width;
	game->minimap.height = height;
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
	actual_width = map_width * MINIMAP_SCALE;
	actual_height = map_height * MINIMAP_SCALE;
	if (!game->minimap.img || game->minimap.width != actual_width
		|| game->minimap.height != actual_height)
	{
		recreate_minimap_image(game, actual_width, actual_height);
	}
	draw_minimap_walls(game, map_width, map_height);
	draw_minimap_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
}
