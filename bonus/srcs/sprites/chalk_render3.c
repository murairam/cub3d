#include "cub3d_bonus.h"

void	render_chalks(t_game *game)
{
	int	i;

	if (!game || !game->chalk_sprites || game->chalk_sprite_count <= 0)
		return ;
	i = 0;
	while (i < game->chalk_sprite_count)
	{
		if (!game->chalk_sprites[i].collected && game->chalk_sprites[i].visible)
		{
			if (game->chalk_sprites[i].img && game->chalk_sprites[i].data)
			{
				if (is_chalk_visible(game, &game->chalk_sprites[i]))
					render_chalk_sprite(game, &game->chalk_sprites[i]);
			}
		}
		i++;
	}
}
