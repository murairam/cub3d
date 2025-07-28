#include "cub3d.h"

void    wall_render(t_ray *ray, t_texture *text, t_game *game, int screenX)
{
	int y;

	y = ray->drawStart - 1;
	while (++y < ray->drawEnd)
	{
		ray->texY = (int)ray->texPos & (text->height - 1);
		ray->texPos += ray->step;
		ray->pixel = (char *)text->data + (ray->texY * text->size_line + ray->texX * (text->bpp / 8));
		ray->color = *(int *)ray->pixel;
		put_pixel(screenX, y, ray->color, game);
	}
}
void    floor_render(t_ray *ray, t_game *game, int screenX)
{
	int y;

	y = ray->drawEnd - 1;
	while (++y < HEIGHT)
		put_pixel(screenX, y, 0x555555, game);
}

void    ceiling_render(t_ray *ray, t_game *game, int screenX)
{
	int y;

	y = -1;
	while (++y < ray->drawStart)
		put_pixel(screenX, y, 0x87CEEB, game);        
}

void    vertical_texture(t_ray *ray, t_texture *text)
{
	ray->step = 1.0f * text->height / ray->lineHeight;
	ray->texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * ray->step;
}

void    texture_cord(t_ray *ray, t_player *player, t_texture *text)
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

void    distance_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - player->x / CUBE + (1 - ray->stepX) / 2.0f) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - player->y / CUBE + (1 - ray->stepY) / 2.0f) / ray->rayDirY;
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

void    dda_finder(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	ray->side = 0;
	while (!ray->hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void    ray_init2(t_ray *ray, t_player *player)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->x / CUBE - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0f - player->x / CUBE) * ray->deltaDistX;
	}

	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->y / CUBE - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0f - player->y / CUBE) * ray->deltaDistY;
	}
}

void    ray_init(t_ray *ray, t_player *player, float rayAngle)
{
	ray->rayDirX = cos(rayAngle);
	ray->rayDirY = sin(rayAngle);
	ray->mapX = (int)(player->x / CUBE);
	ray->mapY = (int)(player->y / CUBE);
	if (ray->rayDirX == 0)
		ray->deltaDistX = BIG_FLOAT;
	else
		ray->deltaDistX = fabs(1.0f / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = BIG_FLOAT;
	else
		ray->deltaDistY = fabs(1.0f / ray->rayDirY);
	ray_init2(ray, player);
}

void    draw_line(t_player *player, t_game *game, float rayAngle, int screenX)
{
	t_ray ray;
	t_texture *text;

	ray_init(&ray, player, rayAngle);
	dda_finder(&ray, game);
	distance_wall(&ray, player);
	if (ray.side == 0)
		text = (ray.rayDirX > 0) ? &game->east : &game->west;
	else
		text = (ray.rayDirY > 0) ? &game->south : &game->north;
	texture_cord(&ray, player, text);
	vertical_texture(&ray, text);
	ceiling_render(&ray, game, screenX);
	wall_render(&ray, text, game, screenX);
	floor_render(&ray, game, screenX);
}
