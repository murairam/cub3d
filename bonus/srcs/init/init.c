#include "cub3d_bonus.h"

static void init_player(t_game *game, t_player *player)
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
    
    // Initialize mouse position and drag state
    game->mouse_x = WIDTH / 2;
    game->mouse_y = HEIGHT / 2;
    game->mouse_dragging = false;
    game->drag_start_x = 0;
    game->drag_start_y = 0;
}

static short texture_init(t_game *game)
{
	game->north.img = mlx_xpm_file_to_image(game->mlx, "incs/assets/textures/Bricks_North1.xpm", &game->north.width, &game->north.height);
	if (!game->north.img)
		return(printf("Error: failed to load Bricks_North.xpm\n"), 1);
	game->north.data = (int *)mlx_get_data_addr(game->north.img, &game->north.bpp, &game->north.size_line, &game->north.endian);
	game->south.img = mlx_xpm_file_to_image(game->mlx, "incs/assets/textures/Bricks_South1.xpm", &game->south.width, &game->south.height);
	if (!game->south.img)
		return(printf("Error: failed to load Bricks_South.xpm\n"), 1);    
	game->south.data = (int *)mlx_get_data_addr(game->south.img, &game->south.bpp, &game->south.size_line, &game->south.endian);
	game->east.img = mlx_xpm_file_to_image(game->mlx, "incs/assets/textures/Bricks_East1.xpm", &game->east.width, &game->east.height);
	if (!game->east.img)
		return(printf("Error: failed to load Bricks_East.xpm\n"), 1);
	game->east.data = (int *)mlx_get_data_addr(game->east.img, &game->east.bpp, &game->east.size_line, &game->east.endian);
	game->west.img = mlx_xpm_file_to_image(game->mlx, "incs/assets/textures/Bricks_West1.xpm",&game->west.width, &game->west.height);
	if (!game->west.img)
		return(printf("Error: failed to load Bricks_West.xpm\n"), 1);
	game->west.data = (int *)mlx_get_data_addr(game->west.img, &game->west.bpp, &game->west.size_line, &game->west.endian);
	
	// Load door texture if available
	if (game->door.name)
	{
		game->door.img = mlx_xpm_file_to_image(game->mlx, game->door.name, &game->door.width, &game->door.height);
		if (!game->door.img)
		{
			printf("Warning: failed to load door texture: %s\n", game->door.name);
			// Use north texture as fallback for doors
			game->door = game->north;
		}
		else
		{
			game->door.data = (int *)mlx_get_data_addr(game->door.img, &game->door.bpp, &game->door.size_line, &game->door.endian);
		}
	}
	else
	{
		// Use north texture as default for doors if no door texture specified
		game->door = game->north;
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int game_init(t_game *game)
{
    init_player(game, &game->player);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "RATS IN THE HOUSE");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (printf("Game Image Error\n"), 1);	
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		return (printf("Game data Error\n"), 1);
	if (texture_init (game))
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

void	init_game(t_game *game)
{
	printf("DEBUG: init_game() called\n");
	ft_memset(game, 0, sizeof(t_game));
	printf("DEBUG: ft_memset completed in init_game\n");
	game->color_c = -1;
	game->color_f = -1;
	printf("DEBUG: Colors initialized to F=%d, C=%d\n",
		game->color_f, game->color_c);
	game->fd = 0;
	game->map = NULL;
	game->north.name = NULL;
	game->south.name = NULL;
	game->east.name = NULL;
	game->west.name = NULL;
	game->door.name = NULL;
	game->doors = NULL;
	game->door_count = 0;
	printf("DEBUG: All pointers set to NULL\n");
}
