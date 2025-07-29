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
}

static short	texture_init(t_game *game)
{
	if (load_texture(game, &game->north,
			"incs/assets/textures/Bricks_North1.xpm"))
		return (1);
	if (load_texture(game, &game->south,
			"incs/assets/textures/Bricks_South1.xpm"))
		return (1);
	if (load_texture(game, &game->east,
			"incs/assets/textures/Bricks_East1.xpm"))
		return (1);
	if (load_texture(game, &game->west,
			"incs/assets/textures/Bricks_West1.xpm"))
		return (1);
	if (game->door.name)
	{
		if (load_texture(game, &game->door, "incs/assets/textures/door.xpm"))
			return (1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

static void	init_game_vars(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RATS IN THE HOUSE");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		printf("Game Image Error\n");
		exit(1);
	}
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
	{
		printf("Game data Error\n");
		exit(1);
	}
}

int	game_init(t_game *game)
{
	init_player(game, &game->player);
	init_game_vars(game);
	if (texture_init(game))
		return (printf("Texture Fail\n"));
	init_minimap(game);
	init_sprites(game);
	init_doors(game);
	game->z_buffer = malloc(sizeof(float) * WIDTH);
	if (!game->z_buffer)
		return (printf("Z-buffer allocation failed\n"), 1);
	game_loop(game);
	return (0);
}
