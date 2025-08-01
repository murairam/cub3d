#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* ************************************************************************** */
/*                                INCLUDES                                   */
/* ************************************************************************** */

# include "../incs/libft/libft.h"
# include "../incs/mlx/mlx.h"
# include "../incs/mlx/mlx_int.h"
# include "parser_bonus.h"
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
# define PI 3.14159265f
# define WIDTH 1280
# define HEIGHT 720
# define CUBE 64
# define LEFT 65361
# define RIGHT 65363
# define SPAWN_NORTH 4.71
# define SPAWN_SOUTH 1.57
# define SPAWN_WEST 3.14159265f
# define SPAWN_EAST 0
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define ESC 65307
# define SPACE 32
# define SHIFT 65505

/* Minimap defines */
# define MINIMAP_SIZE 150
# define MINIMAP_SCALE 8
# define MINIMAP_X 0
# define MINIMAP_Y 0

/* Colors */
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_GRAY 0x808080

/* ************************************************************************** */
/*                                ENUMS                                     */
/* ************************************************************************** */

typedef enum e_wall_dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}					t_wall_dir;

typedef enum e_door_state
{
	DOOR_CLOSED = 0,
	DOOR_OPEN = 1
}					t_door_state;

/* ************************************************************************** */
/*                                STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_arms
{
	bool			is_moving;
	float			idle_speed;
	float			idle_amount;
	float			current_speed;
	float			walking_speed;
	float			walking_amount;
	float			current_amount;
	float			time_increment;
	float			target_intensity;
}					t_arms;

typedef struct s_ray
{
	char			*pixel;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				side;
	int				tex_x;
	int				tex_y;
	int				hit;
	float			step;
	float			tex_pos;
	float			wall_x;
	float			ray_dir_x;
	float			ray_dir_y;
	float			delta_dist_y;
	float			delta_dist_x;
	float			side_dist_x;
	float			side_dist_y;
	float			perp_wall_dist;
}					t_ray;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	char			*orientation;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			left_rot;
	bool			key_right;
	bool			right_rot;
	bool			key_run;
	int				mouse_x;
	int				mouse_y;
}					t_player;

typedef struct s_texture
{
	void			*img;
	char			*name;
	int				*data;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	int				bpp;
	int				x;
	int				y;
}					t_texture;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
}					t_door;

typedef struct s_sprite
{
	float			x;
	float			y;
	int				texture_id;
	float			distance;
	bool			visible;
	int				screen_x;
	int				v_move_screen;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
}					t_sprite;

typedef struct s_minimap
{
	void			*img;
	char			*data;
	int				size_line;
	int				endian;
	int				bpp;
	int				width;
	int				height;
}					t_minimap;

typedef struct s_game
{
	int				fd;
	int				bpp;
	int				endian;
	int				mouse_y;
	int				mouse_x;
	int				color_c;
	int				color_f;
	int				size_line;
	int				door_count;
	int				drag_start_x;
	int				drag_start_y;
	int				sprite_count;
	int				sprite_list_count;
	int				map_width;
	int				map_height;
	char			orientation;
	char			*current_line;
	void			*mlx;
	void			*win;
	void			*img;
	char			**map;
	char			*data;
	float			*z_buffer;
	float			arm_offset;
	float			bob_intensity;
	float			spawn_x;
	float			spawn_y;
	float			bob_time;
	t_door			*doors;
	t_sprite		*sprite_list;
	t_player		player;
	t_minimap		minimap;
	t_texture		left_arm;
	t_texture		right_arm;
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		door;
	t_texture		*sprites;
	t_texture		west;
	bool			mouse_dragging;
	bool			show_minimap;
}					t_game;

/* ************************************************************************** */
/*                                PROTOTYPES                                  */
/* **************************************************************************/

int					ft_error(const char *msg);
void				ft_exit_error(const char *msg);
void				ft_exit_error_with_cleanup(t_game *game, const char *msg);

/* ****************************************************************************/
/*                              MEMORY MANAGEMENT                             */
/* ****************************************************************************/

void				ft_free_split(char **split);
void				ft_free_game(t_game *game);
void				ft_free_mlx(t_game *game);
void				ft_free_bonus(t_game *game);

/* ****************************************************************************/
/*                              PARSER                                        */
/* ****************************************************************************/

void				validate_content(char **map, t_game *game,
						t_list **map_lines);
void				validate_boundaries(char **map, t_game *game,
						t_list **map_lines);
void				validate_chars_and_count(char **map, int *player_count,
						t_game *game, t_list **map_lines);
void				validate_door_consistency(t_game *game, char **map,
						t_list **map_lines);
void				validate_door_texture_file(t_game *game,
						t_list **map_lines);
void				fetch_player_cords(char **map, t_game *game);
void				store_doors(char **map, t_game *game);

/* ****************************************************************************/
/*                              INITIALIZATION                                */
/* ****************************************************************************/

void				init_game(t_game *game);
int					game_init(t_game *game);
short				load_texture(t_game *game, t_texture *texture, char *path);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					close_game(t_game *game);
int					mouse_move(int x, int y, t_game *game);

/* ****************************************************************************/
/*                              GAME LOOP                                     */
/* ****************************************************************************/

void				game_loop(t_game *game);
void				move_player(t_player *player, t_game *game);
void				move_player_keys(t_player *player, t_game *game);
bool				is_wall(t_game *game, float x, float y);
bool				check_collision(float new_x, float new_y, t_game *game);

/* ****************************************************************************/
/*                              RENDERING                                     */
/* ****************************************************************************/

void				put_pixel(int x, int y, int color, t_game *game);
void				clear_image(t_game *game);
void				draw_line(t_player *player, t_game *game, float ray_angle,
						int screen_x);
void				ray_init(t_ray *ray, t_player *player, float ray_angle);
void				dda_finder(t_ray *ray, t_game *game);
void				distance_wall(t_ray *ray, t_player *player);
void				texture_cord(t_ray *ray, t_player *player, t_texture *text);
void				vertical_texture(t_ray *ray, t_texture *text);
void				ceiling_render(t_ray *ray, t_game *game, int screen_x);
void				wall_render(t_ray *ray, t_texture *text, t_game *game,
						int screen_x);
void				floor_render(t_ray *ray, t_game *game, int screen_x);

/* ****************************************************************************/
/*                              MINIMAP                                       */
/* ****************************************************************************/

void				init_minimap(t_game *game);
void				draw_minimap(t_game *game);
void				draw_minimap_player(t_game *game);
void				draw_minimap_walls(t_game *game, int map_width,
						int map_height);
void				put_pixel_minimap(t_game *game, int x, int y, int color);
void				recreate_minimap_image(t_game *game, int width, int height);

/* ****************************************************************************/
/*                              DOORS                                         */
/* ****************************************************************************/

void				init_doors(t_game *game);
void				update_doors(t_game *game);
void				interact_door(t_game *game);
bool				is_door(char c);

#endif
