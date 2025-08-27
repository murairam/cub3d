#include "cub3d_bonus.h"

static void	init_player_position(t_game *game, t_player *player)
{
	player->x = game->spawn_x;
	player->y = game->spawn_y;
	player->pitch = 0.0f;
	if (game->orientation == 'N')
		player->angle = SPAWN_NORTH;
	else if (game->orientation == 'S')
		player->angle = SPAWN_SOUTH;
	else if (game->orientation == 'W')
		player->angle = SPAWN_WEST;
	else if (game->orientation == 'E')
		player->angle = SPAWN_EAST;
}

static void	init_player_keys(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rot = false;
	player->right_rot = false;
	player->pitch_up = false;
	player->pitch_down = false;
}

static void	init_game_state(t_game *game)
{
	game->item_count = 0;
	game->inventory = ft_calloc(MAX_ITEM, sizeof(char *));
	game->mouse_x = WIDTH / 2;
	game->mouse_y = HEIGHT / 2;
	game->bob_time = 0.0f;
	game->bob_intensity = 0.5f;
	game->mouse_dragging = false;
	game->drag_start_x = 0;
	game->drag_start_y = 0;
}

static void	init_player(t_game *game, t_player *player)
{
	init_player_position(game, player);
	init_player_keys(player);
	init_game_state(game);
}

int	game_init(t_game *game)
{
	init_player(game, &game->player);
	init_game_vars(game);
	if (texture_init(game))
		return (ft_error("Failed to initialize textures"), 1);
	init_minimap(game);
	init_doors(game);
	if (!init_chalk_sprite_system(game))
		return (ft_error("Failed to initialize chalk sprite system"), 1);
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		return (ft_error("Z-buffer memory allocation failed"), 1);
	return (0);
}
