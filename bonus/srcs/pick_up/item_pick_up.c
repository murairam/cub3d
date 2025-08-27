#include "cub3d_bonus.h"

int	has_item(t_game *game, char *to_find)
{
	int	i;

	i = -1;
	while (game->item_count > 0 && ++i < game->item_count && i < MAX_ITEM)
	{
		if (ft_strncmp(game->inventory[i], to_find, ft_strlen(to_find)) == 0)
			return (0);
	}
	return (1);
}

void	add_to_inv(t_game *game, char *item)
{
	if (game->item_count < MAX_ITEM)
		game->inventory[game->item_count++] = item;
}

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

void	pick_up_item(t_player *player, t_game *game)
{
	int		map_x;
	int		map_y;
	char	tile;
	int		i;
	double	dx;
	double	dy;
	double	distance;

	map_x = (int)(player->x / CUBE);
	map_y = (int)(player->y / CUBE);
	tile = game->map[map_y][map_x];
	if (game->chalk_sprites && game->chalk_sprite_count > 0)
	{
		for (i = 0; i < game->chalk_sprite_count; i++)
		{
			if (game->chalk_sprites[i].collected
				|| !game->chalk_sprites[i].visible)
				continue ;
			dx = game->chalk_sprites[i].x - player->x;
			dy = game->chalk_sprites[i].y - player->y;
			distance = sqrt(dx * dx + dy * dy);
			if (distance < PICKUP_RADIUS)
			{
				// Pick up the chalk
				game->chalk_sprites[i].visible = 0;
				game->chalk_sprites[i].collected = 1;
				game->chalk_collected++;
				// Add 3 chalk pieces to inventory (each chalk can draw 3 wall tags)
				add_to_inv(game, ft_strdup("Chalk"));
				add_to_inv(game, ft_strdup("Chalk"));
				add_to_inv(game, ft_strdup("Chalk"));
				return ; // Only pick up one chalk at a time
			}
		}
	}
	// Handle other items (legacy system for 'k' key, etc.)
	if (tile == 'k')
	{
		add_to_inv(game, ft_strdup("Key"));
		game->map[map_y][map_x] = '0';
	}
}
