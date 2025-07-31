/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 17:14:05 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_free_mlx_sprites(t_game *game)
{
	int	i;

	if (game->sprites)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			if (game->sprites[i].img)
				mlx_destroy_image(game->mlx, game->sprites[i].img);
			i++;
		}
	}
}

void	ft_free_mlx(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->door.img && game->door.img != game->north.img)
		mlx_destroy_image(game->mlx, game->door.img);
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	ft_free_mlx_sprites(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

static void	ft_free_sprite_names(t_game *game)
{
	int	i;

	if (game->sprites)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			free(game->sprites[i].name);
			i++;
		}
		free(game->sprites);
	}
}

void	ft_free_bonus(t_game *game)
{
	if (game->doors)
		free(game->doors);
	if (game->sprite_list)
		free(game->sprite_list);
	if (game->z_buffer)
		free(game->z_buffer);
	ft_free_sprite_names(game);
}
