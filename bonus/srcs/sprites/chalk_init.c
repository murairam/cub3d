/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:36:25 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:36:26 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			if (game->map[row][col] == 'c' || game->map[row][col] == 'k')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

static void	store_chalk_positions(t_game *game)
{
	int	row;
	int	col;
	int	idx;

	idx = 0;
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (game->map[row] && game->map[row][col])
		{
			if (game->map[row][col] == 'c' || game->map[row][col] == 'k')
				setup_chalk_sprite(game, row, col, idx);
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
	ft_memset(game->chalk_sprites, 0, sizeof(t_chalk_sprite) * count);
	game->chalk_sprite_count = 0;
	store_chalk_positions(game);
	return (1);
}

int	load_chalk_sprite_texture(t_game *game, t_chalk_sprite *sprite)
{
	if (sprite->type == 'c')
		sprite->img = mlx_xpm_file_to_image(game->mlx, TEX_CHALK_ITEM,
				&sprite->width, &sprite->height);
	else if (sprite->type == 'k')
		sprite->img = mlx_xpm_file_to_image(game->mlx, TEX_KEY_ITEM,
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
