#include "cub3d_bonus.h"

static void	random_move(t_game *game, long time, int *stop)
{
	int		counter;
	float	new_x;
	float	new_y;

	counter = -1;
	new_y = (time % game->map_height) * CUBE;
	new_x = (time % ft_strlen(game->map[game->map_height - 1])) * CUBE;
	while (teleport_check(game, new_x, new_y) && ++counter <= 20)
	{
		time += 3;
		new_y = (time % game->map_height) * CUBE;
		new_x = (time % ft_strlen(game->map[game->map_height - 1])) * CUBE;
	}
	if (counter < 20)
	{
		game->random_y = (time % game->map_height) * CUBE;
		game->random_x = (time % ft_strlen(game->map[game->map_height
					- 1])) * CUBE;
		game->random_flag = 1;
	}
	else
		printf("Too many walls...\n");
	*stop += 1;
}

static void	update_fov(t_game *game, long time)
{
	float	time_to_die;
	float	factor;
	float	intensity;
	float	pulse;

	time_to_die = (MAX_TIME - time) / 1000.0f;
	if (time_to_die < 5.0f && game->darken_factor > 0.0f)
	{
		factor = (5.0f - time_to_die) / 5.0f;
		pulse = sin(time * 0.0005f * (1.0f + factor * 5.0f));
		intensity = factor * (PI / 36);
		game->fov = PI / 3 + pulse * intensity;
		game->darken_factor -= 0.000086f;
	}
}

static void	thread_loop(t_game *game, int *counter, long current_time)
{
	if (game->stop != 1)
	{
		pthread_mutex_lock(&game->darken_lock);
		if (game->darken_factor > 0.3)
			game->darken_factor -= 0.0001f;
		pthread_mutex_unlock(&game->darken_lock);
		update_fov(game, current_time);
		if (current_time > MAX_TIME)
			random_move(game, current_time, counter);
		usleep(1000);
	}
}

void	*thread(void *arg)
{
	t_game	*game;
	int		counter;
	long	start_time;
	long	current_time;

	counter = 0;
	game = (t_game *)arg;
	start_time = get_start_time();
	while (game->stop != 1 && counter < MAX_CYCLE)
	{
		current_time = get_timestamp_ms(start_time);
		while (game->stop != 1 && current_time <= MAX_TIME)
		{
			current_time = get_timestamp_ms(start_time);
			thread_loop(game, &counter, current_time);
		}
		if (counter >= MAX_CYCLE)
		{
			game->stop = 1;
			break ;
		}	
		start_time = get_start_time();
		game->darken_factor = 1;
	}
	return (0);
}
