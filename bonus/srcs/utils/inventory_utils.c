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
