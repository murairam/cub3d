/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:21 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 17:56:09 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	thread_should_stop(t_game *game)
{
	int	should_stop;

	pthread_mutex_lock(&game->stop_lock);
	should_stop = game->stop_flag;
	pthread_mutex_unlock(&game->stop_lock);
	return (should_stop);
}

static void	thread_set_stop(t_game *game, int value)
{
	pthread_mutex_lock(&game->stop_lock);
	game->stop_flag = value;
	game->stop = value;
	pthread_mutex_unlock(&game->stop_lock);
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
