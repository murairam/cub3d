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

static int	check_chalk_pickup(t_game *game, t_player *player, int i)
{
	double	dx;
	double	dy;
	double	distance;

	if (game->chalk_sprites[i].collected || !game->chalk_sprites[i].visible)
		return (0);
	dx = game->chalk_sprites[i].x - player->x;
	dy = game->chalk_sprites[i].y - player->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < PICKUP_RADIUS)
	{
	   game->chalk_sprites[i].visible = 0;
	   game->chalk_sprites[i].collected = 1;
	   game->chalk_collected++;
	   for (int c = 0; c < 3; c++)
		   add_to_inv(game, ft_strdup("Chalk"));
	   return (1);
	}
	return (0);
}

static void	check_chalk_sprites(t_game *game, t_player *player)
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

static void	check_legacy_items(t_game *game, t_player *player)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)(player->x / CUBE);
	map_y = (int)(player->y / CUBE);
	tile = game->map[map_y][map_x];
	if (tile == 'k')
	{
		add_to_inv(game, ft_strdup("Key"));
		game->map[map_y][map_x] = '0';
	}
}

void	pick_up_item(t_player *player, t_game *game)
{
	check_chalk_sprites(game, player);
	check_legacy_items(game, player);
}
