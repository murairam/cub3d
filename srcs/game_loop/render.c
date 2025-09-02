#include "cub3d.h"

void	ft_put_pixel(int x, int y, int color, t_game *game)
{
	int	index;
	int	r;
	int	g;
	int	b;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	b = color % 256;
	g = (color / 256) % 256;
	r = (color / 65536) % 256;
	game->data[index] = b;
	game->data[index + 1] = g;
	game->data[index + 2] = r;
}

void	wall_render(t_ray *ray, t_text *text, t_game *game, int screen_x)
{
	int	y;

	y = ray->d_start - 1;
	while (++y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tx_pos % (text->height - 1);
		ray->tx_pos += ray->step;
		ray->pixel = (char *)text->data + (ray->tex_y * text->size_line
				+ ray->tex_x * (text->bpp / 8));
		ray->color = *(int *)ray->pixel;
		ft_put_pixel(screen_x, y, ray->color, game);
	}
}

static void	floor_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = ray->draw_end - 1;
	while (++y < HEIGHT)
		ft_put_pixel(screen_x, y, game->color_f, game);
}

static void	ceiling_render(t_ray *ray, t_game *game, int screen_x)
{
	int	y;

	y = -1;
	while (++y < ray->d_start)
		ft_put_pixel(screen_x, y, game->color_c, game);
}

void	draw_line(t_player *player, t_game *game, float angle, int screen_x)
{
	t_ray	ray;
	t_text	*text;

	ray_init(&ray, player, angle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	if (ray.side == 0 && ray.ray_dir_x > 0)
		text = &game->east;
	else if (ray.side == 0 && ray.ray_dir_x < 0)
		text = &game->west;
	else if (ray.side == 1 && ray.ray_dir_y > 0)
		text = &game->south;
	else
		text = &game->north;
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screen_x);
	wall_render(&ray, text, game, screen_x);
	floor_render(&ray, game, screen_x);
}
