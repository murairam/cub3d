#include "cub3d_bonus.h"

static void	ft_free_mlx(t_game *game)
{
	int	i;

	if (!game->mlx)
		return ;
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->door.img)
		mlx_destroy_image(game->mlx, game->door.img);
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
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
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	ft_free_bonus(t_game *game)
{
	int	i;

	if (game->z_buffer)
		free(game->z_buffer);
	if (game->doors)
		free(game->doors);
	if (game->sprite_list)
		free(game->sprite_list);
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

void	ft_free_game(t_game *game)
{
	char	*cleanup_line;

	if (!game)
		return ;
	printf("DEBUG: Cleaning up memory...\n");
	ft_free_mlx(game);
	free(game->north.name);
	free(game->south.name);
	free(game->east.name);
	free(game->west.name);
	free(game->door.name);
	if (game->map)
		ft_free_split(game->map);
	if (game->current_line)
		free(game->current_line);
	ft_free_bonus(game);
	if (game->fd > 0)
	{
		close(game->fd);
		cleanup_line = get_next_line(game->fd);
		if (cleanup_line)
			free(cleanup_line);
	}
}

void	ft_exit_error_with_cleanup(t_game *game, const char *msg)
{
	ft_free_game(game);
	ft_exit_error(msg);
}

int	close_game(t_game *game)
{
	ft_free_game(game);
	exit(0);
	return (0);
}
