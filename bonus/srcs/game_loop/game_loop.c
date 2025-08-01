#include "cub3d_bonus.h"

void update_arm_bobbing(t_game *game)
{
    t_player	*player;
	t_arms		arms;
 
	player = &game->player;
	arms.walking_amount = 8.0f;
	arms.walking_speed = 5.0f;
	arms.idle_amount = 3.0f;
	arms.idle_speed = 1.5f;
	arms.is_moving = player->key_up || player->key_down || 
                     player->key_left || player->key_right;
	if (arms.is_moving)
		arms.target_intensity = 1.0f;
	else
		arms.target_intensity = 0.5f;
    game->bob_intensity = game->bob_intensity * 0.9f + arms.target_intensity * 0.1f;
	arms.current_speed = arms.idle_speed + (arms.walking_speed - arms.idle_speed) * game->bob_intensity;
	arms.current_amount = arms.idle_amount + (arms.walking_amount - arms.idle_amount) * game->bob_intensity;	
	arms.time_increment = 0.05f;
	game->bob_time += arms.time_increment;
    game->arm_offset = sin(game->bob_time * arms.current_speed) * arms.current_amount;
}

void draw_image_with_transparency(t_game *game, t_texture *src, int x, int y)
{
    unsigned int	color;
    int				*dest_data;
    int				*src_data;
	int				src_j;
    int				i;
	int				j;
    
	if (!src || !src->data || !game || !game->data)
		return ;
	dest_data = (int *)(game->data);
	src_data = (int *)(src->data);
	i = -1;
	while (++i < src->height)
	{
        if (y + i < 0 || y + i >= HEIGHT)
            continue;
        j = -1;
		while (++j < src->width)
		{
            if (x + j < 0 || x + j >= WIDTH)
                continue;
            
			src_j = src->width - 1 - j;
            color = src_data[(i * (src->size_line / 4)) + src_j];
            
            if (color != 0 && color != 0xFF000000)
                dest_data[(y + i) * (game->size_line / 4) + (x + j)] = color;
        }
    }
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	if (!game->data)
		printf("YA UN GROS LABUBUUUUUUUUU\n\n\n\n\n\n\n");
	player = &game->player;
	move_player(player, game);
	update_doors(game);
	clear_image(game);
	i = 0;
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	update_arm_bobbing(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_minimap(game);
	if (game->left_arm.img && game->left_arm.data)
	{
		game->left_arm.x = WIDTH - game->left_arm.width;
		game->left_arm.y = HEIGHT - game->left_arm.height + (int)game->arm_offset + 10;
		draw_image_with_transparency(game, &game->left_arm, game->left_arm.x, game->left_arm.y);
	}
	if (game->right_arm.img && game->right_arm.data)
	{
		game->right_arm.x = 0;
		game->right_arm.y = HEIGHT - game->right_arm.height - (int)game->arm_offset + 10;
		draw_image_with_transparency(game, &game->right_arm, game->right_arm.x, game->right_arm.y);
	}
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_game, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}
