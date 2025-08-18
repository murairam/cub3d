#include "cub3d_bonus.h"

static void	init_player(t_game *game, t_player *player)
{
	player->x = game->spawn_x;
	player->y = game->spawn_y;
	if (game->orientation == 'N')
		player->angle = SPAWN_NORTH;
	else if (game->orientation == 'S')
		player->angle = SPAWN_SOUTH;
	else if (game->orientation == 'W')
		player->angle = SPAWN_WEST;
	else if (game->orientation == 'E')
		player->angle = SPAWN_EAST;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rot = false;
	player->right_rot = false;
	game->mouse_x = WIDTH / 2;
	game->mouse_y = HEIGHT / 2;
	game->bob_time = 0.0f;
	game->bob_intensity = 0.5f;
	game->mouse_dragging = false;
	game->drag_start_x = 0;
	game->drag_start_y = 0;
}

static short	texture_init(t_game *game)
{
	if (load_texture(game, &game->north, TEX_NORTH))
		return (1);
	if (load_texture(game, &game->south, TEX_SOUTH))
		return (1);
	if (load_texture(game, &game->east, TEX_EAST))
		return (1);
	if (load_texture(game, &game->west, TEX_WEST))
		return (1);
	if (load_texture(game, &game->left_arm, TEX_LEFT_ARM))
		return (1);
	if (load_texture(game, &game->right_arm, TEX_RIGHT_ARM))
		return (1);
	if (load_texture(game, &game->mirror, TEX_MIRROR))
		return (1);		
	if (game->door.name)
	{
		if (load_texture(game, &game->door, TEX_DOOR))
			return (1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

static void	init_game_vars(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_exit_error("Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RATS IN THE HOUSE");
	if (!game->win)
		ft_exit_error("Failed to create game window");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		ft_exit_error("Failed to create main game image");
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
		ft_exit_error("Failed to get main game image data");
}

int	game_init(t_game *game)
{
	init_player(game, &game->player);
	init_game_vars(game);
	if (texture_init(game))
		return (ft_error("Failed to initialize textures"), 1);
	init_minimap(game);
	init_doors(game);
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		return (ft_error("Z-buffer memory allocation failed"), 1);
	return (0);
}
