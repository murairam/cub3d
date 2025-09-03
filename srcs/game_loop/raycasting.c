/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:40:37 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:40:38 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_init2(t_ray *ray, t_player *player);

void	ray_init(t_ray *ray, t_player *player, float angle)
{
	ray->hit = 0;
	ray->side = 0;
	ray->ray_dir_x = cos(angle);
	ray->ray_dir_y = sin(angle);
	ray->map_x = (int)player->x / CUBE;
	ray->map_y = (int)player->y / CUBE;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray_init2(ray, player);
}

void	dda_finder(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	distance_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->x / CUBE + (1 - ray->step_x)
				/ 2.0f) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y / CUBE + (1 - ray->step_y)
				/ 2.0f) / ray->ray_dir_y;
	if (ray->perp_wall_dist < 0.1f)
		ray->perp_wall_dist = 0.1f;
	ray->l_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->d_start = -ray->l_height / 2 + HEIGHT / 2;
	if (ray->d_start < 0)
		ray->d_start = 0;
	ray->draw_end = ray->l_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	render_wall(t_game *game, t_ray *ray, int screen_x)
{
	t_text	*text;

	text = get_wall_texture(game, ray);
	if (text && text->data)
	{
		texture_cord(ray, &game->player, text);
		vertical_texture(ray, text);
		wall_render(ray, text, game, screen_x);
	}
}
