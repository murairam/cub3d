#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                INCLUDES                                   */
/* ************************************************************************** */

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "parser.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                DEFINES                                   */
/* ************************************************************************** */

# define BIG_FLOAT 1000000000.0f
# define PI 3.14159265359
# define WIDTH 1280
# define HEIGHT 720
# define CUBE 64
# define LEFT 65361
# define RIGHT 65363
# define SPAWN_NORTH 4.71
# define SPAWN_SOUTH 1.57
# define SPAWN_WEST 3.14159265359
# define SPAWN_EAST 0
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

/* ************************************************************************** */
/*                                DEFINES                                   */
/* ************************************************************************** */

typedef enum e_wall_dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}				t_wall_dir;

/* ************************************************************************** */
/*                                STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_ray
{
	char		*pixel;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			side;
	int			tex_x;
	int			tex_y;
	int			hit;
	float		step;
	float		tex_pos;
	float		wall_x;
	float		ray_dir_x;
	float		ray_dir_y;
	float		delta_dist_y;
	float		delta_dist_x;
	float		side_dist_x;
	float		side_dist_y;
	float		perp_wall_dist;
}				t_ray;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	char		*orientation;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		left_rot;
	bool		key_right;
	bool		right_rot;
}				t_player;

typedef struct s_texture
{
	void		*img;
	char		*name;
	int			*data;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	int			bpp;
}				t_texture;

typedef struct s_game
{
	int			fd;
	int			color_c;
	int			color_f;
	char		*current_line;
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	char		*data;
	int			size_line;
	int			endian;
	int			bpp;
	float		spawn_x;
	float		spawn_y;
	char		orientation;
	t_player	player;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}				t_game;

/* ****************************************************************************/
/*                              ERROR HANDLING                                */
/* ****************************************************************************/

int				ft_error(const char *msg);
void			ft_exit_error(const char *msg);
void			ft_exit_error_with_cleanup(t_game *game, const char *msg);

/* ****************************************************************************/
/*                              MEMORY MANAGEMENT                             */
/* ****************************************************************************/

void			ft_free_split(char **split);
void			ft_free_game(t_game *game);

/* ****************************************************************************/
/*                              INITIALIZATION                                */
/* ****************************************************************************/

void			init_game(t_game *game);
int				game_init(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				close_game(t_game *game);

/* ****************************************************************************/
/*                              GAME LOOP                                     */
/* ****************************************************************************/

void			game_loop(t_game *game);
void			move_player(t_player *player, t_game *game);
void			move_player_keys(t_player *player, t_game *game,
					float cos_angle, float sin_angle);
void			move_forward(t_player *player, t_game *game, float cos_angle,
					float sin_angle);
void			move_backward(t_player *player, t_game *game, float cos_angle,
					float sin_angle);
void			move_left(t_player *player, t_game *game, float cos_angle,
					float sin_angle);
void			move_right(t_player *player, t_game *game, float cos_angle,
					float sin_angle);
void			ray_init(t_ray *ray, t_player *player, float angle);
void			dda_finder(t_ray *ray, t_game *game);
void			distance_wall(t_ray *ray, t_player *player);
void			texture_cord(t_ray *ray, t_player *player, t_texture *text);
void			vertical_texture(t_ray *ray, t_texture *text);
t_texture		*get_wall_texture(t_game *game, t_ray *ray);
void			wall_render(t_ray *ray, t_texture *text, t_game *game,
					int screen_x);

/* ****************************************************************************/
/*                              RENDERING                                     */
/* ****************************************************************************/

void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
void			draw_line(t_player *player, t_game *game, float ray_angle,
					int screen_x);

#endif