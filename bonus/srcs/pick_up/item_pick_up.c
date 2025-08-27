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
	int		i;
	double	dx;
	double	dy;
	double	distance;

	map_x = (int)(player->x / CUBE);
	map_y = (int)(player->y / CUBE);
	tile = game->map[map_y][map_x];
	
	// Check for chalk pickup using sprite system
	if (game->chalk_sprites && game->chalk_sprite_count > 0)
	{
		for (i = 0; i < game->chalk_sprite_count; i++)
		{
			if (game->chalk_sprites[i].collected || !game->chalk_sprites[i].visible)
				continue;
				
			dx = game->chalk_sprites[i].x - player->x;
			dy = game->chalk_sprites[i].y - player->y;
			distance = sqrt(dx * dx + dy * dy);
			
			// Debug output
			printf("Player at (%.1f,%.1f), Chalk #%d at (%.1f,%.1f), Distance: %.1f, Pickup radius: %.1f\n",
			       player->x, player->y, i, game->chalk_sprites[i].x, game->chalk_sprites[i].y, distance, PICKUP_RADIUS);
			
			if (distance < PICKUP_RADIUS)
			{
				// Pick up the chalk
				game->chalk_sprites[i].visible = 0;
				game->chalk_sprites[i].collected = 1;
				game->chalk_collected++;
				
				add_to_inv(game, ft_strdup("Chalk"));
				
				printf("Chalk #%d picked up with 'E'! (%d total collected)\n", 
				       game->chalk_sprites[i].id, game->chalk_collected);
				       
				return; // Only pick up one chalk at a time
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
