#include "cub3d.h"

void	ray_init2(t_ray *ray, t_player *player);

void	ray_init(t_ray *ray, t_player *player, float angle)
{
	ray->hit = 0;
	ray->side = 0;
	ray->rayDirX = cos(angle);
	ray->rayDirY = sin(angle);
	ray->mapX = (int)player->x / CUBE;
	ray->mapY = (int)player->y / CUBE;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray_init2(ray, player);
}

void	dda_finder(t_ray *ray, t_game *game)
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

void	distance_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - player->x / CUBE + (1 - ray->stepX)
				/ 2.0f) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - player->y / CUBE + (1 - ray->stepY)
				/ 2.0f) / ray->rayDirY;
	if (ray->perpWallDist < 0.1f)
		ray->perpWallDist = 0.1f;
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}
