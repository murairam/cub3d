#include "cub3d_bonus.h"

int is_in_tile(t_game *game, int x, int y, char to_find)
{
	if (game->map[y][x] == to_find)
	{	
		if (to_find == 'c')
			game->map[y][x] = '0';
		return (0);
	}
	else
		return (1);
}

int	is_close_enough(t_game *game, t_player *player, char to_find)
{
	int	map_x;
	int	map_y;

	map_x = (int)(player->x / CUBE);
	map_y = (int)(player->y / CUBE);
	//add a 'is in map' function
	if (is_in_tile(game, map_x, map_y, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x + 1, map_y, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x + 1, map_y + 1, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x, map_y + 1, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x - 1, map_y + 1, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x - 1, map_y, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x - 1, map_y  -1, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x, map_y - 1, to_find) == 0)
		return (0);
	else if (is_in_tile(game, map_x + 1, map_y + 1, to_find) == 0)
		return (0);
	else
		return (1);
}

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
	if (is_close_enough(game, player, 'c') == 0)
		add_to_inv(game, ft_strdup("Chalk"));

	else if (tile == 'k')
	{
		add_to_inv(game, ft_strdup("Key"));
		game->map[map_y][map_x] = '0';
	}
}
