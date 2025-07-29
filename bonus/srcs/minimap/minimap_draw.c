/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 16:09:19 by mmiilpal         ###   ########.fr       */
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

void	draw_minimap(t_game *game)
{
	int	map_width;
	int	map_height;
	int	actual_width;
	int	actual_height;

	if (!game->show_minimap)
		return ;
	get_map_dimensions(game->map, game);
	map_width = game->map_width;
	map_height = game->map_height;
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
