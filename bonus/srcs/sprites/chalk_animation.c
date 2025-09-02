/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 00:00:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <sys/time.h>
#include <math.h>

double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	animate_chalk_sprite(t_chalk_sprite *sprite, double delta_time)
{
	double	offset;

	sprite->time += delta_time;
	offset = sin(sprite->time * sprite->frequency) * sprite->amplitude;
	sprite->y = sprite->base_y + offset;
	sprite->x = sprite->base_x;
	if (sprite->time > 1000.0)
		sprite->time = 0.0;
}

void	animate_chalks(t_game *game, double delta_time)
{
	int	i;

	if (!game->chalk_sprites || game->chalk_sprite_count == 0)
		return ;
	game->game_time += delta_time;
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		if (game->chalk_sprites[i].visible && !game->chalk_sprites[i].collected)
			animate_chalk_sprite(&game->chalk_sprites[i], delta_time);
		i++;
	}
}

int	init_chalk_sprite_system(t_game *game)
{
	int	i;

	if (!parse_map_for_chalks(game))
		return (0);
	if (game->chalk_sprite_count == 0)
		return (1);
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		if (!load_chalk_sprite_texture(game, &game->chalk_sprites[i]))
		{
			ft_printf_fd(2, "[ERROR] Failed to load sprite texture for sprite %d\n", i);
			game->chalk_sprites[i].img = NULL;
			game->chalk_sprites[i].data = NULL;
			game->chalk_sprites[i].visible = 0;
			game->chalk_sprites[i].collected = 1;
		}
		i++;
	}
	game->chalk_collected = 0;
	game->game_time = 0.0;
	return (1);
}

void	cleanup_chalk_sprites(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->chalk_sprites && game->chalk_sprite_count > 0)
	{
		i = 0;
		while (i < game->chalk_sprite_count)
		{
			if (game->chalk_sprites[i].img && game->mlx)
				mlx_destroy_image(game->mlx, game->chalk_sprites[i].img);
			game->chalk_sprites[i].img = NULL;
			game->chalk_sprites[i].data = NULL;
			i++;
		}
		free(game->chalk_sprites);
		game->chalk_sprites = NULL;
	}
	game->chalk_sprite_count = 0;
}
