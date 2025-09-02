/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/02 11:49:31 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"

short	init_game_vars(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_printf_fd(2, "Failed to initialize MLX"), 0);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RATS IN THE HOUSE");
	if (!game->win)
		return (ft_printf_fd(2, "Failed to create game window"), 0);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (ft_printf_fd(2, "Failed to create main game image"), 0);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
		return (ft_printf_fd(2, "Failed to get main game image data"), 0);
	return (1);
}
