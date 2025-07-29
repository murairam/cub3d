#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bpp / 8);
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, game);
	}
}

void	vertical_texture(t_ray *ray, t_texture *text)
{
	ray->step = 1.0f * text->height / ray->lineHeight;
	ray->texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2)
		* ray->step;
}

void	texture_cord(t_ray *ray, t_player *player, t_texture *text)
{
	if (ray->side == 0)
		ray->wallX = player->y / CUBE + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = player->x / CUBE + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
	ray->texX = (int)(ray->wallX * (float)(text->width));
	if (ray->side == 0 && ray->rayDirX > 0)
		ray->texX = text->width - ray->texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		ray->texX = text->width - ray->texX - 1;
}

void	ray_init2(t_ray *ray, t_player *player)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->x / CUBE - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->x / CUBE)
			* ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->y / CUBE - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->y / CUBE)
			* ray->deltaDistY;
	}
}
