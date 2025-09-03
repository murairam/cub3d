/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:35:21 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 16:50:33 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include "cub3d_bonus.h"

static int thread_should_stop(t_game *game)
{
    int should_stop;
    pthread_mutex_lock(&game->stop_lock);
    should_stop = game->stop_flag;
    pthread_mutex_unlock(&game->stop_lock);
    return should_stop;
}

static void thread_set_stop(t_game *game, int value)
{
    pthread_mutex_lock(&game->stop_lock);
    game->stop_flag = value;
    game->stop = value;  // Keep both for compatibility
    pthread_mutex_unlock(&game->stop_lock);
}

static void random_move(t_game *game, long time, int *stop)
{
    int counter = -1;
    float new_x, new_y;
    
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
        // Safely update random position
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

static void update_fov(t_game *game, long time)
{
    float time_to_die = (MAX_TIME - time) / 1000.0f;
    
    if (time_to_die < 5.0f)
    {
        // Check current darken_factor safely
        pthread_mutex_lock(&game->darken_lock);
        int should_update = (game->darken_factor > 0.0f);
        pthread_mutex_unlock(&game->darken_lock);
        
        if (should_update)
        {
            float factor = (5.0f - time_to_die) / 5.0f;
            float pulse = sin(time * 0.0005f * (1.0f + factor * 5.0f));
            float intensity = factor * (PI / 36);
            float new_fov = PI / 3 + pulse * intensity;
            
            // Update FOV safely
            pthread_mutex_lock(&game->fov_lock);
            game->fov = new_fov;
            pthread_mutex_unlock(&game->fov_lock);
            
            // Update darken factor safely
            pthread_mutex_lock(&game->darken_lock);
            game->darken_factor -= 0.000086f;
            pthread_mutex_unlock(&game->darken_lock);
        }
    }
}

static void thread_loop(t_game *game, int *counter, long current_time)
{
    if (!thread_should_stop(game))
    {
        // Update darken factor
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

void *thread(void *arg)
{
    t_game *game = (t_game *)arg;
    int counter = 0;
    long start_time = get_start_time();
    long current_time;
    
    while (!thread_should_stop(game) && counter < MAX_CYCLE)
    {
        current_time = get_timestamp_ms(start_time);
        
        while (!thread_should_stop(game) && current_time <= MAX_TIME)
        {
            current_time = get_timestamp_ms(start_time);
            thread_loop(game, &counter, current_time);
        }
        
        if (counter >= MAX_CYCLE)
        {
            thread_set_stop(game, 1);
            break;
        }
        
        start_time = get_start_time();
        
        // Reset darken factor safely
        pthread_mutex_lock(&game->darken_lock);
        game->darken_factor = 1;
        pthread_mutex_unlock(&game->darken_lock);
    }
    
    return NULL;
}
