/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_cache.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 20:32:27 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <math.h>

void	init_chalk_cache(t_chalk_sprite *sprite)
{
	sprite->cache.distance = -1.0;
	sprite->cache.angle_diff = 0.0;
	sprite->cache.player_angle = 0.0;
	sprite->cache.screen_x = -1;
	sprite->cache.needs_update = true;
	sprite->cache.in_fov = false;
	sprite->cache.visible = false;
	sprite->cache.visibility_timer = 0;
	sprite->cache.cached_visibility = false;
}

bool	should_update_cache(t_game *game, t_chalk_sprite *sprite)
{
	double	dx;
	double	dy;
	double	new_distance;
	double	distance_diff;
	double	angle_diff;

	if (sprite->cache.needs_update)
		return (true);
	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	new_distance = sqrt(dx * dx + dy * dy);
	distance_diff = fabs(new_distance - sprite->cache.distance);
	if (distance_diff > CACHE_UPDATE_THRESHOLD)
		return (true);
	
	// Also update if player angle changed significantly
	angle_diff = fabs(game->player.angle - sprite->cache.player_angle);
	if (angle_diff > 0.1)
		return (true);
	
	return (false);
}

void	update_chalk_cache(t_game *game, t_chalk_sprite *sprite)
{
	double	dx;
	double	dy;
	double	sprite_angle;
	double	angle_diff;

	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	sprite->cache.distance = sqrt(dx * dx + dy * dy);
	sprite_angle = atan2(dy, dx);
	angle_diff = normalize_angle(sprite_angle - game->player.angle);
	sprite->cache.angle_diff = angle_diff;
	sprite->cache.player_angle = game->player.angle;
	sprite->cache.in_fov = (fabs(angle_diff) <= FOV_HALF_RADIANS);
	sprite->cache.screen_x = (int)(WIDTH / 2 + (angle_diff * WIDTH)
			/ FOV_RADIANS);
	sprite->cache.needs_update = false;
}

bool	get_cached_visibility(t_game *game, t_chalk_sprite *sprite)
{
	if (sprite->cache.visibility_timer > 0)
	{
		sprite->cache.visibility_timer--;
		return (sprite->cache.cached_visibility);
	}
	sprite->cache.cached_visibility = is_chalk_visible(game, sprite);
	sprite->cache.visibility_timer = VISIBILITY_CACHE_FRAMES;
	return (sprite->cache.cached_visibility);
}

void	invalidate_all_chalk_caches(t_game *game)
{
	int	i;

	if (!game->chalk_sprites)
		return ;
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		game->chalk_sprites[i].cache.needs_update = true;
		i++;
	}
}
