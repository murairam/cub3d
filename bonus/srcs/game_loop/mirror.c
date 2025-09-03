/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:34 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:37:35 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	text_filler(t_game *game, t_ray *reflect, t_text **text, t_ray *ray)
{
	if (game->map[reflect->map_y][reflect->map_x] == 'D')
		*text = &game->door;
	else if (reflect->side == 0)
	{
		if (reflect->ray_dir_x > 0)
			*text = &game->east;
		else
			*text = &game->west;
	}
	else
	{
		if (reflect->ray_dir_y > 0)
			*text = &game->south;
		else
			*text = &game->north;
	}
	(*text)->l_height = (int)(HEIGHT / ray->perp_wall_dist);
	(*text)->d_start = -(*text)->l_height / 2 + HEIGHT / 2;
	if ((*text)->d_start < 0)
		(*text)->d_start = 0;
	(*text)->draw_end = (*text)->l_height / 2 + HEIGHT / 2;
	if ((*text)->draw_end >= HEIGHT)
		(*text)->draw_end = HEIGHT - 1;
}

static void	compute_reflection_color(t_ray *reflect, t_text *text, t_game *game)
{
	float	factor;

	reflect->tex_y = (int)reflect->tx_pos;
	if (reflect->tex_y < 0)
		reflect->tex_y = 0;
	if (reflect->tex_y >= text->height)
		reflect->tex_y = text->height - 1;
	reflect->tx_pos += reflect->step;
	if (reflect->tex_x < 0)
		reflect->tex_x = 0;
	if (reflect->tex_x >= text->width)
		reflect->tex_x = text->width - 1;
	reflect->pixel = (char *)text->data + (reflect->tex_y * text->size_line
			+ reflect->tex_x * (text->bpp / 8));
	factor = factor_calculator(reflect, game);
	reflect->color = dim_color(*(int *)reflect->pixel, factor);
}

void	reflect_put_pixel(t_ray *reflect, t_text *text,
		t_game *game, int screenX)
{
	int		y;
	int		pitch_offset;
	int		render_y;

	pitch_offset = -(int)(game->player.pitch * HEIGHT * 0.3f);
	y = text->d_start - 1;
	while (++y < text->draw_end)
	{
		render_y = y + pitch_offset;
		if (render_y >= 0 && render_y < HEIGHT)
		{
			compute_reflection_color(reflect, text, game);
			draw_pixel(screenX, render_y, reflect->color, game);
		}
		else
			reflect->tx_pos += reflect->step;
	}
}

t_text	*reflection_init(t_ray *ray, t_game *game, int screenX)
{
	t_player	p_player;
	t_text		*text;
	t_ray		refl;
	float		reflect_angle;

	refl = *ray;
	if (ray->side == 0)
		refl.ray_dir_x = -ray->ray_dir_x;
	else
		refl.ray_dir_y = -ray->ray_dir_y;
	p_player.x = (ray->map_x + 0.5f) * CUBE + 0.01f * ray->ray_dir_x * CUBE;
	p_player.y = (ray->map_y + 0.5f) * CUBE + 0.01f * ray->ray_dir_y * CUBE;
	reflect_angle = atan2f(refl.ray_dir_y, refl.ray_dir_x);
	ray_init(&refl, &p_player, reflect_angle);
	dda_finder(&refl, game);
	distance_wall(&refl, &p_player);
	text_filler(game, &refl, &text, ray);
	ceiling_render(ray, game, screenX);
	texture_cord(&refl, &p_player, text);
	refl.step = 1.0 * text->height / text->l_height;
	refl.tx_pos = (text->d_start - HEIGHT / 2 + text->l_height / 2) * refl.step;
	reflect_put_pixel(&refl, text, game, screenX);
	return (text);
}

void	reflection(t_ray *ray, t_game *game, int screenX)
{
	t_text		*text;

	text = reflection_init(ray, game, screenX);
	if (game->map[ray->map_y][ray->map_x] == 'M')
		mirror_texture(game, ray, text, screenX);
	floor_render(ray, game, screenX);
}
