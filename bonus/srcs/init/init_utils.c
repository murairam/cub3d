/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:38:27 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:38:28 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_player_position(t_game *game, t_player *player)
{
	player->x = game->spawn_x;
	player->y = game->spawn_y;
	player->pitch = 0.0f;
	if (game->orientation == 'N')
		player->angle = SPAWN_NORTH;
	else if (game->orientation == 'S')
		player->angle = SPAWN_SOUTH;
	else if (game->orientation == 'W')
		player->angle = SPAWN_WEST;
	else if (game->orientation == 'E')
		player->angle = SPAWN_EAST;
}

static void	init_player_keys(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rot = false;
	player->right_rot = false;
	player->pitch_up = false;
	player->pitch_down = false;
	player->key_f_pressed = false;
}

static void	init_game_state(t_game *game)
{
	game->item_count = 0;
	game->inventory = ft_calloc(MAX_ITEM, sizeof(char *));
	if (!game->inventory)
		close_with_print(game, "Error: Malloc failed");
	game->mouse_x = WIDTH / 2;
	game->mouse_y = HEIGHT / 2;
	game->bob_time = 0.0f;
	game->bob_intensity = 0.5f;
	game->mouse_dragging = false;
	game->drag_start_x = 0;
	game->drag_start_y = 0;
}

static void	init_player(t_game *game, t_player *player)
{
	init_player_position(game, player);
	init_player_keys(player);
}

int	game_init(t_game *game)
{
	init_player(game, &game->player);
	init_game_state(game);
	init_mlx(game);
	if (texture_init(game))
		ft_exit_error_with_cleanup(game, NULL);
	init_minimap(game);
	init_doors(game);
	if (!init_chalk_sprite_system(game))
		close_with_print(game, "Error: Item init");
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		close_with_print(game, "Error: Buffer init");
	game->ray_table.initialized = false;
	return (0);
}
