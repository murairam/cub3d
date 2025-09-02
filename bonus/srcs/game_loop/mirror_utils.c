#include "cub3d_bonus.h"

t_text	*choose_mirror_texture(t_ray *ray, t_game *game, float nx, float ny)
{
	t_text	*tex;
	float	len;
	float	vx;
	float	vy;
	float	dot;

	tex = &game->mirror;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		nx = -1.0f;
	else if (ray->side == 0 && ray->ray_dir_x <= 0)
		nx = 1.0f;
	else if (ray->ray_dir_y > 0)
		ny = -1.0f;
	else
		ny = 1.0f;
	len = sqrtf(ray->ray_dir_x * ray->ray_dir_x
			+ ray->ray_dir_y * ray->ray_dir_y);
	vx = -ray->ray_dir_x / len;
	vy = -ray->ray_dir_y / len;
	dot = fabsf(vx * nx + vy * ny);
	if (dot > 0.95f && game->char_mirror.data)
		tex = &game->char_mirror;
	return (tex);
}

static void	render_mirror_pixel(t_ray *ray, t_text *mir_tex, t_game *game,
				int screenX)
{
	int		render_y;
	int		pitch_offset;
	float	factor;

	pitch_offset = -(int)(game->player.pitch * HEIGHT * 0.3f);
	render_y = game->y + pitch_offset;
	if (render_y >= 0 && render_y < HEIGHT)
	{
		ray->tex_y = (int)ray->tx_pos % (mir_tex->height - 1);
		ray->tx_pos += ray->step;
		if (ray->tex_x >= mir_tex->width)
			ray->tex_x = mir_tex->width - 1;
		ray->pixel = (char *)mir_tex->data + (ray->tex_y
				* mir_tex->size_line + ray->tex_x * (mir_tex->bpp / 8));
		factor = factor_calculator(ray, game);
		ray->color = dim_color(*(int *)ray->pixel, factor);
		if (ray->color != 0 && (unsigned)ray->color != 0xFF000000)
			draw_pixel(screenX, render_y, ray->color, game);
	}
	else
		ray->tx_pos += ray->step;
}

void	mirror_texture(t_game *game, t_ray *ray, t_text *text, int screenX)
{
	t_text	*mir_tex;

	mir_tex = &game->mirror;
	mir_tex = choose_mirror_texture(ray, game, 0, 0);
	texture_cord(ray, &game->player, mir_tex);
	ray->step = 1.0 * mir_tex->height / text->l_height;
	ray->tx_pos = (text->d_start - HEIGHT / 2 + text->l_height / 2) * ray->step;
	game->y = text->d_start - 1;
	while (++game->y < text->draw_end)
		render_mirror_pixel(ray, mir_tex, game, screenX);
}
