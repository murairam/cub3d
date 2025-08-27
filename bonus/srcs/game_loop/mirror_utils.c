#include "cub3d_bonus.h"

static void	setup_mirror_texture(t_game *game, t_ray *ray, t_text *text,
				t_text **mir_tex)
{
	int	pitch_offset;

	pitch_offset = -(int)(game->player.pitch * HEIGHT * 0.3f);
	*mir_tex = &game->mirror;
	texture_cord(ray, &game->player, *mir_tex);
	ray->step = 1.0 * (*mir_tex)->height / text->l_height;
	ray->tx_pos = (text->d_start - HEIGHT / 2 + text->l_height / 2)
		* ray->step;
	game->y = text->d_start - 1;
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
		factor = 1.0f / (1.0f + ray->perp_wall_dist * 0.1f) + 0.2f;
		if (ray->side == 0)
			factor *= 0.8f;
		ray->color = dim_color(*(int *)ray->pixel, factor);
		if (ray->color != 0 && (unsigned)ray->color != 0xFF000000)
			put_pixel(screenX, render_y, ray->color, game);
	}
	else
		ray->tx_pos += ray->step;
}

void	mirror_texture(t_game *game, t_ray *ray, t_text *text, int screenX)
{
	t_text	*mir_tex;

	setup_mirror_texture(game, ray, text, &mir_tex);
	while (++game->y < text->draw_end)
		render_mirror_pixel(ray, mir_tex, game, screenX);
}
