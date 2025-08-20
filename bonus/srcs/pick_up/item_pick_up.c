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

void	pick_up_item(t_player *player, t_game *game)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)(player->x / CUBE);
	map_y = (int)(player->y / CUBE);
	tile = game->map[map_y][map_x];
	if (tile == 'c')
	{
		add_to_inv(game, ft_strdup("Chalk"));
		game->map[map_y][map_x] = '0';
	}
	else if (tile == 'k')
	{
		add_to_inv(game, ft_strdup("Key"));
		game->map[map_y][map_x] = '0';
	}
}
