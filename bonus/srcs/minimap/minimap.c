/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/07/29 12:31:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_minimap(t_game *game)
{
	game->minimap.width = MINIMAP_SIZE;
	game->minimap.height = MINIMAP_SIZE;
	game->minimap.img = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!game->minimap.img)
		ft_exit_error_with_cleanup(game, "Failed to create minimap image");
	game->minimap.data = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bpp, &game->minimap.size_line,
			&game->minimap.endian);
	if (!game->minimap.data)
		ft_exit_error_with_cleanup(game, "Failed to get minimap data address");
	game->show_minimap = true;
}
