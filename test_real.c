#include "bonus/incs/cub3d_bonus.h"
#include <math.h>

bool is_chalk_visible(t_game *game, t_chalk_sprite *sprite)
{
    double dx = sprite->x - game->player.x;
    double dy = sprite->y - game->player.y;
    double distance = sqrt(dx * dx + dy * dy);
    
    if (distance < 32.0)
        return (true);
    return (true); // simplified for testing
}
