/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:40:17 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:40:18 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_game *game, t_player *player)
{
	player->x = game->spawn_x;
	player->y = game->spawn_y;
	if (game->orientation == 'N')
		player->angle = SPAWN_NORTH;
	else if (game->orientation == 'S')
		player->angle = SPAWN_SOUTH;
	else if (game->orientation == 'W')
		player->angle = SPAWN_WEST;
	else if (game->orientation == 'E')
		player->angle = SPAWN_EAST;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rot = false;
	player->right_rot = false;
}

static short	load_texture(t_game *game, t_text *texture, char *path)
{
	char	*err;

	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		err = ft_strjoin("Error\nfailed to load texture ", path);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
		free(err);
		return (1);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (0);
}

static short	texture_init(t_game *game)
{
	if (load_texture(game, &game->north, game->north.name))
		return (1);
	if (load_texture(game, &game->south, game->south.name))
		return (1);
	if (load_texture(game, &game->east, game->east.name))
		return (1);
	if (load_texture(game, &game->west, game->west.name))
		return (1);
	return (0);
}

int	game_init(t_game *game)
{
	init_player(game, &game->player);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error\nFailed to initialize mlx\n", 2), 1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RATS IN THE HOUSE");
	if (!game->win)
		return (ft_putstr_fd("Error\nFailed to create window\n", 2), 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (ft_putstr_fd("Error\nFailed to create image\n", 2), 1);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		return (ft_putstr_fd("Error\nFailed to get image data\n", 2), 1);
	if (texture_init(game))
		return (1);
	return (0);
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->color_c = -1;
	game->color_f = -1;
	game->fd = 0;
	game->map = NULL;
	game->north.name = NULL;
	game->south.name = NULL;
	game->east.name = NULL;
	game->west.name = NULL;
}
