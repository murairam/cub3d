/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/02 17:08:05 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	normalize_angle(double angle)
{
	while (angle > M_PI)
		angle -= 2 * M_PI;
	while (angle < -M_PI)
		angle += 2 * M_PI;
	return (angle);
}

int	is_sprite_in_bounds(int x, int y)
{
	return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

static void	setup_chalk_sprite_utils(t_game *game, int row, int col, int idx)
{
	game->chalk_sprites[idx].width = 0;
	game->chalk_sprites[idx].height = 0;
	game->chalk_sprites[idx].bpp = 0;
	game->chalk_sprites[idx].size_line = 0;
	game->chalk_sprites[idx].endian = 0;
	game->chalk_sprites[idx].visible = 1;
	game->chalk_sprites[idx].collected = 0;
	game->chalk_sprites[idx].id = idx;
	game->chalk_sprites[idx].time = idx * 0.3;
	game->chalk_sprites[idx].amplitude = CHALK_AMPLITUDE;
	game->chalk_sprites[idx].frequency = CHALK_FREQUENCY + (idx * 0.05);
	game->chalk_sprites[idx].type = game->map[row][col];
	game->map[row][col] = '0';
	game->chalk_sprite_count++;
}

void	setup_chalk_sprite(t_game *game, int row, int col, int idx)
{
	double	world_x;
	double	world_y;

	world_x = col * CUBE + (CUBE / 2);
	world_y = row * CUBE + (CUBE / 2);
	idx = game->chalk_sprite_count;
	game->chalk_sprites[idx].x = world_x;
	game->chalk_sprites[idx].y = world_y;
	game->chalk_sprites[idx].base_x = world_x;
	game->chalk_sprites[idx].base_y = world_y;
	game->chalk_sprites[idx].img = NULL;
	game->chalk_sprites[idx].data = NULL;
	setup_chalk_sprite_utils(game, row, col, idx);
}
