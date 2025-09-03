/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:21 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:35:22 by mmiilpal         ###   ########.fr       */
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

void	thread_set_stop(t_game *game, int value)
{
	pthread_mutex_lock(&game->stop_lock);
	game->stop_flag = value;
	game->stop = value;
	pthread_mutex_unlock(&game->stop_lock);
}

static void	apply_random_position(t_game *game, float new_x, float new_y)
{
	pthread_mutex_lock(&game->game_state_lock);
	game->random_y = new_y;
	game->random_x = new_x;
	game->random_flag = 1;
	pthread_mutex_unlock(&game->game_state_lock);
}

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
		apply_random_position(game, new_x, new_y);
	else
		ft_printf_fd(2, "Error: Too many walls...\n");
	*stop += 1;
}
