/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:57 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 15:53:24 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_random_position(t_game *game, int *use_random,
	float *random_x, float *random_y)
{
	pthread_mutex_lock(&game->game_state_lock);
	*use_random = game->random_flag;
	*random_x = game->random_x;
	*random_y = game->random_y;
	if (*use_random)
		game->random_flag = 0;
	pthread_mutex_unlock(&game->game_state_lock);
}

void	render_wall_complete(t_ray *ray, t_game *game, int screen_x)
{
	t_text	*text;

	if (game->map[ray->map_y][ray->map_x] == 'M')
		return (reflection(ray, game, screen_x));
	text = get_wall_texture(game, ray);
	texture_cord(ray, &game->player, text);
	vertical_texture(ray, text);
	ceiling_render(ray, game, screen_x);
	wall_render(ray, text, game, screen_x);
	floor_render(ray, game, screen_x);
}
