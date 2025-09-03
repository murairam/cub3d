/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pick_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:06 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:37:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	add_single_chalk_item(t_game *game, char item)
{
	char	*chalk_item;

	if (item == 'c')
		chalk_item = ft_strdup("Chalk");
	else
		chalk_item = ft_strdup("Key");
	if (!chalk_item)
		close_with_print(game, "Error: Malloc failed");
	add_to_inv(game, chalk_item);
	if (item == 'c')
		game->print_flag = HELP_CHALK;
	else if (item == 'k')
		game->print_flag = HELP_KEY;
}

static void	add_chalk_items_to_inventory(t_game *game, char item)
{
	int	i;

	i = -1;
	if (item == 'c')
	{
		while (++i < 3)
			add_single_chalk_item(game, item);
	}
	else
		add_single_chalk_item(game, item);
}

static int	check_chalk_pickup(t_game *game, t_player *player, int i)
{
	double	dx;
	double	dy;
	double	distance_squared;

	if (game->chalk_sprites[i].collected || !game->chalk_sprites[i].visible)
		return (0);
	dx = game->chalk_sprites[i].x - player->x;
	dy = game->chalk_sprites[i].y - player->y;
	distance_squared = dx * dx + dy * dy;
	if (distance_squared < PICKUP_RADIUS * PICKUP_RADIUS)
	{
		game->chalk_sprites[i].visible = 0;
		game->chalk_sprites[i].collected = 1;
		game->chalk_collected++;
		add_chalk_items_to_inventory(game, game->chalk_sprites[i].type);
		return (1);
	}
	return (0);
}

void	check_chalk_sprites(t_game *game, t_player *player)
{
	int	i;

	if (!game->chalk_sprites || game->chalk_sprite_count <= 0)
		return ;
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		check_chalk_pickup(game, player, i);
		i++;
	}
}
