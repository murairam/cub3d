/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 17:56:16 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	random_move(t_game *game, long time, int *stop)
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
		pthread_mutex_lock(&game->game_state_lock);
		game->random_y = new_y;
		game->random_x = new_x;
		game->random_flag = 1;
		pthread_mutex_unlock(&game->game_state_lock);
	}
	else
		ft_printf_fd(2, "Error: Too many walls...\n");
	*stop += 1;
}

void	update_fov(t_game *game, long time)
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

void	thread_loop(t_game *game, int *counter, long current_time)
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
