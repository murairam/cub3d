/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:25:01 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/25 18:59:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	draw_map(t_vars *vars)
{
	int	pos[2];

	vars->coll = mlx_xpm_file_to_image(vars->mlx, PATH_C, &pos[0], &pos[1]);
	vars->exit = mlx_xpm_file_to_image(vars->mlx, PATH_E, &pos[0], &pos[1]);
	vars->player = mlx_xpm_file_to_image(vars->mlx, PATH_P, &pos[0], &pos[1]);
	vars->wall = mlx_xpm_file_to_image(vars->mlx, PATH_W, &pos[0], &pos[1]);
	vars->space = mlx_xpm_file_to_image(vars->mlx, PATH_S, &pos[0], &pos[1]);
	vars->bonus = mlx_xpm_file_to_image(vars->mlx, PATH_B, &pos[0], &pos[1]);
}

int	end_game(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->exit);
	mlx_destroy_image(vars->mlx, vars->wall);
	mlx_destroy_image(vars->mlx, vars->space);
	mlx_destroy_image(vars->mlx, vars->player);
	mlx_destroy_image(vars->mlx, vars->coll);
	mlx_destroy_image(vars->mlx, vars->bonus);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_map(vars->map.map);
	exit(0);
	return (0);
}

void	put_image(t_vars *vars, void *img_ptr)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img_ptr, \
			vars->pos.x * SIZE, vars->pos.y * SIZE);
}

void	put_bonus(t_vars *vars, void *img_ptr)
{
	vars->pos.x = 0;
	while (vars->pos.y == vars->map.height && vars->pos.x < vars->map.width)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, img_ptr, \
			vars->pos.x * SIZE, vars->pos.y * SIZE);
		vars->pos.x++;
	}
	ft_moves_to_win(vars);
}

int	render(t_vars *vars)
{
	vars->pos.y = 0;
	while (vars->pos.y < vars->map.height)
	{
		vars->pos.x = 0;
		while (vars->pos.x < vars->map.width)
		{
			if (vars->map.map[vars->pos.y][vars->pos.x] == WALL)
				put_image(vars, vars->wall);
			else if (vars->map.map[vars->pos.y][vars->pos.x] == COLLECTIBLE)
				put_image(vars, vars->coll);
			else if (vars->map.map[vars->pos.y][vars->pos.x] == EXIT)
				put_image(vars, vars->exit);
			else if (vars->map.map[vars->pos.y][vars->pos.x] == PLAYER)
				put_image(vars, vars->player);
			else if (vars->map.map[vars->pos.y][vars->pos.x] == SPACE)
				put_image(vars, vars->space);
			vars->pos.x++;
		}
		vars->pos.y++;
	}
	put_bonus(vars, vars->bonus);
	return (0);
}
