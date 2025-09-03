/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:38:30 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:38:31 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->color_c = -1;
	game->color_f = -1;
	game->fd = 0;
	game->map = NULL;
	game->north.name = NULL;
	game->south.name = NULL;
	game->east.name = NULL;
	game->west.name = NULL;
	game->door.name = NULL;
	game->ray_table.initialized = false;
	game->sprite_count = 0;
	game->door_count = 0;
	game->spawn_x = 0;
	game->spawn_y = 0;
	game->orientation = 0;
	game->fov = PI / 3;
	game->stop = 0;
	game->darken_factor = 1;
	game->print_flag = 0;
	game->random_flag = 0;
	game->minimap_toggle = false;
	pthread_mutex_init(&game->darken_lock, NULL);
}
