#include "cub3d_bonus.h"

bool	is_door(char c)
{
	return (c == 'D');
}

void	init_doors(t_game *game)
{
	int	i;

	if (game->door_count == 0)
		return ;
	i = 0;
	while (i < game->door_count)
	{
		game->doors[i].state = DOOR_CLOSED;
		i++;
	}
}
