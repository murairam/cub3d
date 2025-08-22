#include "cub3d_bonus.h"

void	update_fov(t_game *game, long time)
{
	float	time_to_die;
	float	factor;
	float	intensity;
	float	pulse;

	time_to_die = (MAX_TIME - time) / 1000.0f;
	if (time_to_die < 5.0f)
	{
		factor = (5.0f - time_to_die) / 5.0f;
		pulse = sin(time * 0.0005f * (1.0f + factor * 5.0f));
		intensity = factor * (PI / 36);
		game->fov = PI / 3 + pulse * intensity;
	}
}

long	get_timestamp_ms(long start_time)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	time -= start_time;
	return (time);
}

static long	get_start_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

void	*thread(void *arg)
{
	t_game	*game;
	long	start_time;
	long	current_time;

	game = (t_game *)arg;
	start_time = get_start_time();
	while (game->stop != 1)
	{
		current_time = get_timestamp_ms(start_time);
		pthread_mutex_lock(&game->darken_lock);
		game->darken_factor -= 0.0001f;
		if (game->darken_factor < 0.3)
			game->darken_factor = 0.3;
		pthread_mutex_unlock(&game->darken_lock);
		update_fov(game, current_time);
		if (current_time > MAX_TIME)
			break ;
		usleep(1000);
	}
	return (0);
}
