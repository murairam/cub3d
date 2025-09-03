/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:10 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:35:11 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	close_with_print(t_game *game, char *to_print)
{
	ft_printf_fd(2, "%s\n", to_print);
	close_game(game);
}

void	ft_free_wall_textures(t_game *game)
{
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->north_chalk.img)
		mlx_destroy_image(game->mlx, game->north_chalk.img);
	if (game->south_chalk.img)
		mlx_destroy_image(game->mlx, game->south_chalk.img);
	if (game->east_chalk.img)
		mlx_destroy_image(game->mlx, game->east_chalk.img);
	if (game->west_chalk.img)
		mlx_destroy_image(game->mlx, game->west_chalk.img);
}
