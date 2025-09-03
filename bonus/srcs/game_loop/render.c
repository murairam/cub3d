/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:57 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 16:52:25 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static	t_text	*north_south_walls(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_y > 0 && game->map[ray->map_y][ray->map_x] == '1')
		return (&game->south);
	else if (ray->ray_dir_y > 0 && game->map[ray->map_y][ray->map_x] == '2')
		return (&game->south_chalk);
	else if (game->map[ray->map_y][ray->map_x] == '1')
		return (&game->north);
	else
		return (&game->north_chalk);
}

static	t_text	*east_west_walls(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x > 0 && game->map[ray->map_y][ray->map_x] == '1')
		return (&game->east);
	else if (ray->ray_dir_x > 0 && game->map[ray->map_y][ray->map_x] == '2')
		return (&game->east_chalk);
	else if (game->map[ray->map_y][ray->map_x] == '1')
		return (&game->west);
	else
		return (&game->west_chalk);
}

static t_text	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->map_y >= 0 && ray->map_y < game->map_height
		&& ray->map_x >= 0 && game->map[ray->map_y]
		&& ray->map_x < (int)ft_strlen(game->map[ray->map_y])
		&& (game->map[ray->map_y][ray->map_x] == 'D'
		|| game->map[ray->map_y][ray->map_x] == 'X'))
	{
		if (game->map[ray->map_y][ray->map_x] == 'D')
			return (&game->door);
		else if (game->map[ray->map_y][ray->map_x] == 'X')
			return (&game->exit);
	}
	if (ray->side == 0)
		return (east_west_walls(game, ray));
	else
		return (north_south_walls(game, ray));
}

static void	fish_eye_correction(t_ray *ray, t_player *player, float ray_angle)
{
	float	angle_diff;
	int		half_height;

	angle_diff = ray_angle - player->angle;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	ray->perp_wall_dist *= cos(angle_diff);
	ray->l_height = (int)(HEIGHT / ray->perp_wall_dist);
	half_height = HEIGHT / 2;
	ray->d_start = -ray->l_height / 2 + half_height;
	if (ray->d_start < 0)
		ray->d_start = 0;
	ray->draw_end = ray->l_height / 2 + half_height;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT;
}

void draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
{
    t_ray ray;
    t_text *text;
    
    // Safely check and use random position
    pthread_mutex_lock(&game->game_state_lock);
    int use_random = game->random_flag;
    float random_x = game->random_x;
    float random_y = game->random_y;
    if (use_random)
        game->random_flag = 0;  // Reset flag after using
    pthread_mutex_unlock(&game->game_state_lock);
    
    if (use_random)
    {
        player->x = random_x;
        player->y = random_y;
    }
    else
    {
        ray_init(&ray, player, ray_angle);
        dda_finder(&ray, game);
        distance_wall(&ray, player);
        fish_eye_correction(&ray, player, ray_angle);
        
        if (game->map[ray.map_y][ray.map_x] == 'M')
            return reflection(&ray, game, screen_x);
        
        text = get_wall_texture(game, &ray);
        texture_cord(&ray, player, text);
        vertical_texture(&ray, text);
        ceiling_render(&ray, game, screen_x);
        wall_render(&ray, text, game, screen_x);
        floor_render(&ray, game, screen_x);
    }
}
