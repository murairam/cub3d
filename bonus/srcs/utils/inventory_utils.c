#include "cub3d_bonus.h"
int chalk_count_in_inventory(t_game *game)
{
	int count = 0;
	for (int i = 0; i < game->item_count; i++) {
		if (ft_strncmp(game->inventory[i], "Chalk", 5) == 0)
			count++;
	}
	return count;
}

void	add_to_inv(t_game *game, char *item)
{
	if (game->item_count < MAX_ITEM)
		game->inventory[game->item_count++] = item;
}
