/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 00:00:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"

static void	draw_chalk_square(t_game *game, int center_x, int center_y)
{
	int				x;
	int				y;
	int				chalk_size;
	char			*dst;
	unsigned int	chalk_color;

	chalk_color = 0x00FF00;
	chalk_size = MINIMAP_SCALE / 3;
	y = center_y - chalk_size / 2;
	while (y <= center_y + chalk_size / 2)
	{
		x = center_x - chalk_size / 2;
		while (x <= center_x + chalk_size / 2)
		{
			if (x >= 0 && x < game->minimap.width && y >= 0
				&& y < game->minimap.height)
			{
				dst = game->minimap.data + (y * game->minimap.size_line
						+ x * (game->minimap.bpp / 8));
				*(unsigned int *)dst = chalk_color;
			}
			x++;
		}
		y++;
	}
}

static void	draw_chalk_tile_on_minimap(t_game *game, int map_x, int map_y)
{
	int	player_map_x;
	int	player_map_y;
	int	rel_x;
	int	rel_y;

	player_map_x = (int)(game->player.x / CUBE);
	player_map_y = (int)(game->player.y / CUBE);
	rel_x = map_x - player_map_x + MINIMAP_TILES_X / 2;
	rel_y = map_y - player_map_y + MINIMAP_TILES_Y / 2;
	if (rel_x < 0 || rel_x >= MINIMAP_TILES_X || rel_y < 0
		|| rel_y >= MINIMAP_TILES_Y)
		return ;
	draw_chalk_square(game, rel_x * MINIMAP_SCALE + MINIMAP_SCALE / 2,
		rel_y * MINIMAP_SCALE + MINIMAP_SCALE / 2);
}

void	draw_chalks_on_minimap(t_game *game)
{
	int	i;
	int	map_x;
	int	map_y;

	if (!game || !game->chalk_sprites)
		return ;
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		if (!game->chalk_sprites[i].collected)
		{
			map_x = (int)(game->chalk_sprites[i].x / CUBE);
			map_y = (int)(game->chalk_sprites[i].y / CUBE);
			draw_chalk_tile_on_minimap(game, map_x, map_y);
		}
		i++;
	}
}
