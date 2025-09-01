#include "cub3d_bonus.h"

static void end_screen(t_game *game)
{
	if (game->stop == 1)
		mlx_put_image_to_window(game->mlx, game->win,
			game->screen_over.img, 0, 0);
	if (game->stop == 2)
		mlx_put_image_to_window(game->mlx, game->win,
			game->screen_win.img, 0, 0);
}

static void	render_rays(t_game *game, t_player *player)
{
	float	fraction;
	float	start_x;
	int		i;

	i = 0;
	fraction = game->fov / WIDTH;
	start_x = player->angle - PI / 6;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
}

int	draw_loop(t_game *game)
{
	t_player		*player;
	double			delta_time;

	if (game->stop != 0)
		end_screen(game);
	else
	{
		delta_time = delta_calculator();
		player = &game->player;
		move_player(player, game);
		clear_image(game);
		render_rays(game, player);
		animate_chalks(game, delta_time);
		render_chalks(game);
		update_arm_bobbing(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
		draw_minimap(game);
		render_game_arms(game);
		print_handler(game, player);
	}
	return (0);
}

void	game_loop(t_game *game)
{
	if (pthread_create(&game->thread, NULL, thread, game))
		return ;
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_game, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}
