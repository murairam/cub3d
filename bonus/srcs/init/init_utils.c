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
	player->key_f_pressed = false;
}

static short	init_game_state(t_game *game)
{
	game->inventory = ft_calloc(MAX_ITEM, sizeof(char *));
	if (!game->inventory)
		return (0);
	game->item_count = 0;
	game->mouse_x = WIDTH / 2;
	game->mouse_y = HEIGHT / 2;
	game->bob_time = 0.0f;
	game->bob_intensity = 0.5f;
	game->mouse_dragging = false;
	game->drag_start_x = 0;
	game->drag_start_y = 0;
	return (1);
}

static short	init_player(t_game *game, t_player *player)
{
	init_player_position(game, player);
	init_player_keys(player);
	if (!init_game_state(game))
		return (0);
	return (1);
}

int	game_init(t_game *game)
{
	if (!init_player(game, &game->player))
	{
		ft_error("Failed to initialize player");
		close_game(game);
		return (1);
	}
	if (!init_game_vars(game))
		return (close_game(game), 1);
	if (texture_init(game))
	{
		ft_error("Failed to initialize textures");
		close_game(game);
		return (1);
	}
	init_minimap(game);
	init_doors(game);
	if (!init_chalk_sprite_system(game))
		return (ft_error("Failed to initialize chalk sprite system"), 1);
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		return (ft_error("Z-buffer memory allocation failed"), 1);
	game->ray_table.initialized = false;
	return (0);
}
