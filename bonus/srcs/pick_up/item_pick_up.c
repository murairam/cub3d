#include "cub3d_bonus.h"

static void	add_single_chalk_item(t_game *game)
{
	char	*chalk_item;

	chalk_item = ft_strdup("Chalk");
	if (chalk_item)
	{
		add_to_inv(game, chalk_item);
		game->print_flag = HELP_CHALK;
	}
}

static void	add_chalk_items_to_inventory(t_game *game)
{
	add_single_chalk_item(game);
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
		add_chalk_items_to_inventory(game);
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

void	check_legacy_items(t_game *game, t_player *player)
{
	if (is_close_enough(game, player, 'c') == 0)
		add_to_inv(game, ft_strdup("Chalk"));
	else if (is_close_enough(game, player, 'k') == 0)
		add_to_inv(game, ft_strdup("Key"));
}
