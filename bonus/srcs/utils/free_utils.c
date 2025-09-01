#include "cub3d_bonus.h"

static void	ft_free_mlx_sprites(t_game *game)
{
	int	i;

	if (game->sprites)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			if (game->sprites[i].img)
				mlx_destroy_image(game->mlx, game->sprites[i].img);
			i++;
		}
	}
}

void	ft_free_image_textures(t_game *game)
{
	ft_free_wall_textures(game);
	if (game->door.img && game->door.img != game->north.img)
		mlx_destroy_image(game->mlx, game->door.img);
	if (game->exit.img && game->exit.img != game->north.img)
		mlx_destroy_image(game->mlx, game->exit.img);
	if (game->left_arm.img)
		mlx_destroy_image(game->mlx, game->left_arm.img);
	if (game->right_arm.img)
		mlx_destroy_image(game->mlx, game->right_arm.img);
	if (game->right_chalk.img)
		mlx_destroy_image(game->mlx, game->right_chalk.img);
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	if (game->mirror.img)
		mlx_destroy_image(game->mlx, game->mirror.img);
	if (game->char_mirror.img)
		mlx_destroy_image(game->mlx, game->char_mirror.img);
	if (game->screen_over.img)
		mlx_destroy_image(game->mlx, game->screen_over.img);
}

void	ft_free_mlx(t_game *game)
{
	if (!game->mlx)
		return ;
	ft_free_image_textures(game);
	ft_free_mlx_sprites(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

static void	ft_free_sprite_names(t_game *game)
{
	int	i;

	if (game->sprites)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			free(game->sprites[i].name);
			i++;
		}
		free(game->sprites);
	}
}

void	ft_free_bonus(t_game *game)
{
	if (game->doors)
		free(game->doors);
	if (game->sprite_list)
		free(game->sprite_list);
	if (game->z_buffer)
		free(game->z_buffer);
	ft_free_sprite_names(game);
}
