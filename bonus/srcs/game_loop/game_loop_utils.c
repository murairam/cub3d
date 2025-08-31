#include "cub3d_bonus.h"

double	delta_calculator(void)
{
	static double	last_time = 0.0;
	double			current_time;
	double			delta_time;

	current_time = get_current_time();
	if (last_time == 0.0)
		last_time = current_time;
	delta_time = current_time - last_time;
	last_time = current_time;
	return (delta_time);
}

static void	calculate_arm_values(t_arms *arms, t_player *player, t_game *game)
{
	arms->walking_amount = 8.0f;
	arms->walking_speed = 5.0f;
	arms->idle_amount = 3.0f;
	arms->idle_speed = 1.5f;
	if (player->key_up || player->key_down || player->key_left
		|| player->key_right)
		arms->is_moving = 1;
	else
		arms->is_moving = 0;
	if (arms->is_moving)
		arms->target_intensity = 1.0f;
	else
		arms->target_intensity = 0.5f;
	game->bob_intensity = game->bob_intensity * 0.9f + arms->target_intensity
		* 0.1f;
	arms->current_speed = arms->idle_speed + (arms->walking_speed
			- arms->idle_speed) * game->bob_intensity;
	arms->current_amount = arms->idle_amount + (arms->walking_amount
			- arms->idle_amount) * game->bob_intensity;
}

void	update_arm_bobbing(t_game *game)
{
	t_player	*player;
	t_arms		arms;

	player = &game->player;
	calculate_arm_values(&arms, player, game);
	arms.time_increment = 0.05f;
	game->bob_time += arms.time_increment * arms.current_speed;
	game->arm_offset = sinf(game->bob_time) * arms.current_amount;
}
