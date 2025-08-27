/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 00:00:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <string.h>

static int	count_chalks(t_game *game)
{
	int	row;
	int	col;
	int	count;

	count = 0;
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row] && game->map[row][col])
		{
			if (game->map[row][col] == 'c')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

static void	setup_chalk_sprite(t_game *game, int row, int col)
{
	double	world_x;
	double	world_y;
	int		idx;

	world_x = col * CUBE + (CUBE / 2);
	world_y = row * CUBE + (CUBE / 2);
	idx = game->chalk_sprite_count;
	
	// Initialize all fields to prevent corruption
	game->chalk_sprites[idx].img = NULL;
	game->chalk_sprites[idx].data = NULL;
	game->chalk_sprites[idx].width = 0;
	game->chalk_sprites[idx].height = 0;
	game->chalk_sprites[idx].bpp = 0;
	game->chalk_sprites[idx].size_line = 0;
	game->chalk_sprites[idx].endian = 0;
	game->chalk_sprites[idx].x = world_x;
	game->chalk_sprites[idx].y = world_y;
	game->chalk_sprites[idx].base_x = world_x;
	game->chalk_sprites[idx].base_y = world_y;
	game->chalk_sprites[idx].visible = 1;
	game->chalk_sprites[idx].collected = 0;
	game->chalk_sprites[idx].id = idx;
	game->chalk_sprites[idx].time = idx * 0.3;
	game->chalk_sprites[idx].amplitude = CHALK_AMPLITUDE;
	game->chalk_sprites[idx].frequency = CHALK_FREQUENCY + (idx * 0.05);
	game->map[row][col] = '0';
	game->chalk_sprite_count++;
}

static void	store_chalk_positions(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row] && game->map[row][col])
		{
			if (game->map[row][col] == 'c')
				setup_chalk_sprite(game, row, col);
			col++;
		}
		row++;
	}
}

int	parse_map_for_chalks(t_game *game)
{
	int	count;

	count = count_chalks(game);
	if (count == 0)
	{
		game->chalk_sprites = NULL;
		game->chalk_sprite_count = 0;
		return (1);
	}
	game->chalk_sprites = malloc(sizeof(t_chalk_sprite) * count);
	if (!game->chalk_sprites)
		return (0);
	// Zero initialize the memory to prevent corruption
	memset(game->chalk_sprites, 0, sizeof(t_chalk_sprite) * count);
	game->chalk_sprite_count = 0;
	store_chalk_positions(game);
	return (1);
}

int	load_chalk_sprite_texture(t_game *game, t_chalk_sprite *sprite)
{
	sprite->img = mlx_xpm_file_to_image(game->mlx, TEX_CHALK_ITEM,
			&sprite->width, &sprite->height);
	if (!sprite->img)
		return (0);
	sprite->data = (int *)mlx_get_data_addr(sprite->img, &sprite->bpp,
			&sprite->size_line, &sprite->endian);
	if (!sprite->data)
	{
		mlx_destroy_image(game->mlx, sprite->img);
		return (0);
	}
	return (1);
}
