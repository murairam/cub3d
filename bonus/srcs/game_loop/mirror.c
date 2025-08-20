#include "cub3d_bonus.h"

int	dim_color(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

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

void	reflect_put_pixel(t_ray *reflect, t_text *text,
		t_game *game, int screenX)
{
	int	y;

	y = text->d_start - 1;
	while (++y < text->draw_end)
	{
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
		reflect->color = *(int *)reflect->pixel;
		reflect->color = dim_color(reflect->color, 0.6f);
		put_pixel(screenX, y, reflect->color, game);
	}
}

void	mirror_texture(t_game *game, t_ray *ray, t_text *text, int screenX)
{
	t_text	*mir_tex;

	mir_tex = &game->mirror;
	texture_cord(ray, &game->player, mir_tex);
	ray->step = 1.0 * mir_tex->height / text->l_height;
	ray->tx_pos = (text->d_start - HEIGHT / 2 + text->l_height / 2) * ray->step;
	game->y = text->d_start - 1;
	while (++game->y < text->draw_end)
	{
		ray->tex_y = (int)ray->tx_pos;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		if (ray->tex_y >= mir_tex->height)
			ray->tex_y = mir_tex->height - 1;
		ray->tx_pos += ray->step;
		if (ray->tex_x < 0)
			ray->tex_x = 0;
		if (ray->tex_x >= mir_tex->width)
			ray->tex_x = mir_tex->width - 1;
		ray->pixel = (char *)mir_tex->data + (ray->tex_y * mir_tex->size_line
				+ ray->tex_x * (mir_tex->bpp / 8));
		ray->color = *(int *)ray->pixel;
		if (ray->color != 0 && (unsigned)ray->color != 0xFF000000)
			put_pixel(screenX, game->y, ray->color, game);
	}
}

void	reflection(t_ray *ray, t_game *game, int screenX)
{
	t_ray		refl;
	t_player	p_player;
	t_text		*text;
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
	if (game->mirror.data)
		mirror_texture(game, ray, text, screenX);
	floor_render(ray, game, screenX);
}
