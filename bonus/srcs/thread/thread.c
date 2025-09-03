/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:21 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:35:22 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_fov(t_game *game, long time)
{
	float	time_to_die;
	float	factor;
	float	new_fov;

	time_to_die = (MAX_TIME - time) / 1000.0f;
	if (time_to_die < 5.0f)
	{
		pthread_mutex_lock(&game->darken_lock);
		if (game->darken_factor > 0.0f)
		{
			factor = (5.0f - time_to_die) / 5.0f;
			new_fov = PI / 3 + sin(time * 0.0005f * (1.0f + factor * 5.0f))
				* factor * (PI / 36);
			pthread_mutex_lock(&game->fov_lock);
			game->fov = new_fov;
			pthread_mutex_unlock(&game->fov_lock);
			game->darken_factor -= 0.000086f;
		}
		pthread_mutex_unlock(&game->darken_lock);
	}
}

static void	thread_loop(t_game *game, int *counter, long current_time)
{
	if (!thread_should_stop(game))
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

static void	thread_cycle(t_game *game, int *counter, long *start_time)
{
	long	current_time;

	current_time = get_timestamp_ms(*start_time);
	while (!thread_should_stop(game) && current_time <= MAX_TIME)
	{
		current_time = get_timestamp_ms(*start_time);
		thread_loop(game, counter, current_time);
	}
	if (*counter >= MAX_CYCLE)
		thread_set_stop(game, 1);
	else
	{
		*start_time = get_start_time();
		pthread_mutex_lock(&game->darken_lock);
		game->darken_factor = 1;
		pthread_mutex_unlock(&game->darken_lock);
	}
}

void	*thread(void *arg)
{
	t_game	*game;
	int		counter;
	long	start_time;

	game = (t_game *)arg;
	counter = 0;
	start_time = get_start_time();
	while (!thread_should_stop(game) && counter < MAX_CYCLE)
		thread_cycle(game, &counter, &start_time);
	return (NULL);
}
