/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:03:22 by obajja            #+#    #+#             */
/*   Updated: 2025/08/05 18:23:41 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			step;

	player = &game->player;
	move_player(player, game);
	update_doors(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	step = 3;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		draw_line(player, game, start_x, i + 1);		
		draw_line(player, game, start_x, i + 2);		
		start_x += step * fraction;
		i += step;
	}
	update_arm_bobbing(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_minimap(game);
	game->Left_arm.x = WIDTH - game->Left_arm.width;
	game->Left_arm.y = HEIGHT - game->Left_arm.height + (int)game->arm_offset + 10;
	draw_image_with_transparency(game, &game->Left_arm, game->Left_arm.x, game->Left_arm.y);
	game->Right_arm.x = 0;
	game->Right_arm.y = HEIGHT - game->Right_arm.height - (int)game->arm_offset + 10;
	draw_image_with_transparency(game, &game->Right_arm, game->Right_arm.x, game->Right_arm.y);
	return (0);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_game, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(game->win, 5, 1L << 3, mouse_release, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}
