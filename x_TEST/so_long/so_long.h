/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:12:12 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/04/30 16:21:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define NAME "so_long"

# include "incs/libft/libft.h"
# include "incs/mlx/mlx.h"
# include "incs/mlx/mlx_int.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_HEIGHT 30
# define MAX_WIDTH 50

# define PATH_S "xpms/space.xpm"
# define PATH_W "xpms/wall.xpm"
# define PATH_C "xpms/coll.xpm"
# define PATH_E "xpms/exit.xpm"
# define PATH_P "xpms/player.xpm"
# define PATH_B "xpms/bonus.xpm"

# define SPACE '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307

# define A_UP 65362
# define A_DOWN 65364
# define A_LEFT 65361
# define A_RIGHT 65363

# define SIZE 33

# define TRUE 1
# define FALSE 0

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	int		num_of_collectibles;
	int		num_of_exits;
	int		num_of_players;
	int		colls_in_wallet;
	int		exit;
	int		moves;
	t_pos	player_pos;
	t_pos	game_pos;
}			t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	*path;
	t_map	map;
	char	**duped_map;
	void	*img;
	void	*player;
	void	*exit;
	void	*coll;
	void	*wall;
	void	*space;
	void	*bonus;
	int		fd;
	t_pos	pos;
}			t_vars;

// main.c
int			main(int argc, char **argv);

// parser.c
void		write_to_map(t_vars *vars);
int			parsing(t_vars *vars);

// init.c
void		initialize_game(t_vars *vars, char *map);
void		init_map(t_vars *vars);
char		**duplicate_map(t_vars *vars);

// graphic_manager.c
void		draw_map(t_vars *vars);
int			end_game(t_vars *vars);
void		put_image(t_vars *vars, void *img_ptr);
int			render(t_vars *vars);

// moves.c
int			check_next_move(t_map *game, t_vars *vars);
int			game_keycodes(int keycode, t_vars *vars);
int			i_pressed_a_key(int keycode, t_vars *vars);

// utils.c
int			ft_linelen(char *s);
void		error(char *msg);
void		free_map(char **map);
int			get_map_height(char *file);

// map_checker.c
int			is_rectangular(t_vars *vars);
int			is_ber(char *path);
int			is_components_valid(t_vars *vars);
int			is_map_walled(t_vars *vars);
int			unknown_character(int c);

// path_checker.c
void		floodfill(t_vars *vars, int x, int y);
int			is_path_valid(t_vars *vars);
void		position_player(t_vars *vars);

void		ft_moves_to_win(t_vars *vars);
#endif
