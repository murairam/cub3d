#include "cub3d_bonus.h"

int	dim_color(int color, float factor)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	r = (int)(r * factor);
	g = (int)(g * factor);
	b = (int)(b * factor);

	//testing
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	return (r << 16) | (g << 8) | b;
}

void	text_filler(t_game *game, t_ray *reflected, t_texture **text, t_ray *ray)
{
	if (game->map[reflected->map_y][reflected->map_x] == 'D')
		*text = &game->door;
	else if (reflected->side == 0)
	{
		if (reflected->ray_dir_x > 0) 
			*text = &game->east;
		else
			*text = &game->west;
	}
	else
	{
		if (reflected->ray_dir_y > 0)
			*text = &game->south;
		else
			*text = &game->north;
	}
	(*text)->lineHeight = (int)(HEIGHT / ray->perp_wall_dist);
	(*text)->drawStart = -(*text)->lineHeight / 2 + HEIGHT / 2;
	if ((*text)->drawStart < 0)
		(*text)->drawStart = 0;
	(*text)->drawEnd = (*text)->lineHeight / 2 + HEIGHT / 2;
	if ((*text)->drawEnd >= HEIGHT)
		(*text)->drawEnd = HEIGHT - 1;
}
void reflected_put_pixel(t_ray *reflected, t_texture *text, t_game *game, int screenX)
{
	int y;

	y = text->drawStart - 1;
	while(++y < text->drawEnd)
	{
		reflected->tex_y = (int)reflected->tex_pos;
		if (reflected->tex_y < 0)
			reflected->tex_y = 0;
		if (reflected->tex_y >= text->height)
			reflected->tex_y = text->height - 1;
		reflected->tex_pos += reflected->step;
		if (reflected->tex_x < 0)
			reflected->tex_x = 0;
		if (reflected->tex_x >= text->width)
			reflected->tex_x = text->width - 1;
		reflected->pixel = (char *)text->data + (reflected->tex_y * text->size_line
			+ reflected->tex_x * (text->bpp / 8));
		reflected->color = *(int *)reflected->pixel;
		reflected->color = dim_color(reflected->color, 0.6f);
		put_pixel(screenX, y, reflected->color, game);
	}
}
void	mirror_texture(t_game *game, t_ray *ray, t_texture *text, int screenX)
{
	int			y;
	t_texture	*mirror_text;

	mirror_text = &game->mirror;
    texture_cord(ray, &game->player, mirror_text);
    ray->step = 1.0 * mirror_text->height / text->lineHeight;
    ray->tex_pos = (text->drawStart - HEIGHT / 2 + text->lineHeight / 2) * ray->step;
    y = text->drawStart - 1;
	while (++y < text->drawEnd)
    {
        ray->tex_y = (int)ray->tex_pos;
        if (ray->tex_y < 0)
            ray->tex_y = 0;
        if (ray->tex_y >= mirror_text->height)
            ray->tex_y = mirror_text->height - 1;
        ray->tex_pos += ray->step;
        
        if (ray->tex_x < 0)
            ray->tex_x = 0;
        if (ray->tex_x >= mirror_text->width)
            ray->tex_x = mirror_text->width - 1;
        
        ray->pixel = (char *)mirror_text->data + (ray->tex_y * mirror_text->size_line
            + ray->tex_x * (mirror_text->bpp / 8));
        ray->color = *(int *)ray->pixel;
        if (ray->color != 0 && (unsigned)ray->color != 0xFF000000)
        {
            put_pixel(screenX, y, ray->color, game);
        }
    }
}

void reflection(t_ray *ray, t_game *game, int screenX)
{
	t_ray reflected = *ray;
	t_player pseudo_player;
	t_texture *text;
	float reflected_angle;
	
	if (ray->side == 0)
		reflected.ray_dir_x = -ray->ray_dir_x;
	else
		reflected.ray_dir_y = -ray->ray_dir_y;
	
	float offset = 0.01f;
	pseudo_player.x = (ray->map_x + 0.5f) * CUBE + offset * ray->ray_dir_x * CUBE;
	pseudo_player.y = (ray->map_y + 0.5f) * CUBE + offset * ray->ray_dir_y * CUBE;

	reflected_angle = atan2f(reflected.ray_dir_y, reflected.ray_dir_x);
	ray_init(&reflected, &pseudo_player, reflected_angle);
	dda_finder(&reflected, game);
	distance_wall(&reflected, &pseudo_player);
	text_filler(game, &reflected, &text, ray);
	ceiling_render(ray, game, screenX);
	texture_cord(&reflected, &pseudo_player, text);
	reflected.step = 1.0 * text->height / text->lineHeight;
	reflected.tex_pos = (text->drawStart - HEIGHT / 2 + text->lineHeight / 2) * reflected.step;
	reflected_put_pixel(&reflected, text, game, screenX);
	mirror_texture(game, ray, text, screenX);
	floor_render(ray, game, screenX);
}

static t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->map_y >= 0 && ray->map_y < game->map_height
		&& ray->map_x >= 0 && game->map[ray->map_y]
		&& ray->map_x < (int)ft_strlen(game->map[ray->map_y])
		&& game->map[ray->map_y][ray->map_x] == 'D')
		return (&game->door);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->east);
		return (&game->west);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->south);
		return (&game->north);
	}
}

void	draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
{
	t_ray		ray;
	t_texture	*text;

	ray_init(&ray, player, ray_angle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	if (game->map[ray.map_y][ray.map_x] == 'M')
	{
		reflection(&ray, game, screen_x);
		return;
	}
	text = get_wall_texture(game, &ray);
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screen_x);
	wall_render(&ray, text, game, screen_x);
	floor_render(&ray, game, screen_x);
}
