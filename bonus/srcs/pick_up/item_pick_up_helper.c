#include "cub3d_bonus.h"

int	remove_from_inv(t_game *game, char *to_remove)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->item_count && i < MAX_ITEM)
	{
		if (ft_strncmp(game->inventory[i], to_remove,
				ft_strlen(to_remove)) == 0)
		{
			free(game->inventory[i]);
			j = i;
			while (j < game->item_count - 1)
			{
				game->inventory[j] = game->inventory[j + 1];
				j++;
			}
			game->inventory[game->item_count - 1] = NULL;
			game->item_count--;
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_in_tile(char *map_tile, char to_find, bool replace)
{
	if (*map_tile == to_find && replace == true)
	{
		*map_tile = '0';
		return (0);
	}
	else if (*map_tile == to_find && replace == false)
		return (0);
	else
		return (1);
}

int	is_close_enough(t_game *game, t_player *player, char to_find)
{
	double	dx;
	double	dy;
	double	distance_squared;
	int		i;

	i = -1;
	while (++i < game->chalk_sprite_count)
	{
		if (!game->chalk_sprites[i].collected
			&& game->chalk_sprites[i].visible)
		{
			dx = game->chalk_sprites[i].x - player->x;
			dy = game->chalk_sprites[i].y - player->y;
			distance_squared = dx * dx + dy * dy;
			if (distance_squared < PICKUP_RADIUS * PICKUP_RADIUS
				&& game->chalk_sprites[i].type == to_find)
				return (0);
		}
	}
	return (1);
}

int	has_item(t_game *game, char *to_find)
{
	int	i;

	i = 0;
	while (i < game->item_count && i < MAX_ITEM)
	{
		if (ft_strncmp(game->inventory[i], to_find,
				ft_strlen(to_find)) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	pick_up_item(t_player *player, t_game *game)
{
	check_chalk_sprites(game, player);
	check_legacy_items(game, player);
}
