/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:41:42 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 14:15:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* ************************************************************************** */
/*                                INCLUDES                                   */
/* ************************************************************************** */

# include "../../incs/libft/libft.h"
# include "../../incs/mlx/mlx.h"
# include "../../incs/mlx/mlx_int.h"
# include "parser_bonus.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                                DEFINES                                   */
/* ************************************************************************** */

# define MAX_TIME			15000000000000
# define BIG_FLOAT			1000000000.0f
# define PI					3.14159265f
# define WIDTH				1920
# define HEIGHT				1080
# define CUBE				64
# define LEFT				65361
# define RIGHT				65363
# define UP					65362
# define DOWN				65364
# define MAX_PITCH			1.047197551f
# define SPAWN_NORTH		4.71
# define SPAWN_SOUTH		1.57
# define SPAWN_WEST			3.14159265f
# define SPAWN_EAST			0
# define W					119
# define A					97
# define S					115
# define D					100
# define E					101
# define F					102
# define M					109
# define ESC				65307
# define SPACE				32
# define SHIFT				65505
# define MAX_ITEM			5
# define MAX_CYCLE			3

/* Minimap defines */
# define MINIMAP_SIZE		150
# define MINIMAP_SCALE		10
# define MINIMAP_TILES_X	25
# define MINIMAP_TILES_Y	18
# define MINIMAP_X			0
# define MINIMAP_Y			0
# define MINIMAP_ALPHA		0.7f

/* Colors */
# define COLOR_WHITE		0xFFFFFF
# define COLOR_BLACK		0x000000
# define COLOR_RED			0xFF0000
# define COLOR_GREEN		0x00FF00
# define COLOR_BLUE			0x0000FF
# define COLOR_YELLOW		0xFFFF00
# define COLOR_GRAY			0x808080

/* Texture paths */
# define TEX_NORTH			"incs/assets/textures/Bricks_North.xpm"
# define TEX_SOUTH			"incs/assets/textures/Bricks_South.xpm"
# define TEX_EAST			"incs/assets/textures/Bricks_East.xpm"
# define TEX_WEST			"incs/assets/textures/Bricks_West.xpm"
# define TEX_CHALK_N		"incs/assets/textures/Bricks_NorthX.xpm"
# define TEX_CHALK_S		"incs/assets/textures/Bricks_SouthX.xpm"
# define TEX_CHALK_E		"incs/assets/textures/Bricks_EastX.xpm"
# define TEX_CHALK_W		"incs/assets/textures/Bricks_WestX.xpm"
# define TEX_LEFT_ARM		"incs/assets/textures/LeftArm.xpm"
# define TEX_RIGHT_ARM		"incs/assets/textures/RightArm.xpm"
# define TEX_DOOR			"incs/assets/textures/door.xpm"
# define TEX_EXIT			"incs/assets/textures/exit.xpm"
# define TEX_MIRROR			"incs/assets/textures/Bricks_Mirror_Help.xpm"
# define TEX_CHAR_MIRROR	"incs/assets/textures/Char_Mirror_Help.xpm"
# define TEX_GAME_OVER		"incs/assets/textures/GameOver.xpm"
# define TEX_GAME_WIN		"incs/assets/textures/GameWin.xpm"
# define TEX_CHALK_ITEM		"incs/assets/textures/chalk.xpm"
# define TEX_KEY_ITEM		"incs/assets/textures/key.xpm"

/* Sprite constants */
# define MAX_SPRITES		50
# define PICKUP_RADIUS		48.0
# define MAX_RENDER_DISTANCE	500.0
# define FOV_DEGREES		60.0
# define FOV_RADIANS		1.0471975511965976
# define FOV_HALF_RADIANS	0.5235987755982988
# define CHALK_AMPLITUDE	0.2
# define CHALK_FREQUENCY	3.0
# define SPRITE_SCALE_FACTOR	72.0
# define SPRITE_HEIGHT_OFFSET	120

/* Performance optimization constants */
# define ANIM_TABLE_SIZE	360
# define GRID_SIZE			8
# define CACHE_UPDATE_THRESHOLD	32.0
# define VISIBILITY_CACHE_FRAMES	4
# define CLOSE_VISIBILITY_RANGE		64.0

/* Helpers printed */
# define NO_PRINT			110
# define NO_CHALK			111
# define PICK_CHALK			112
# define PICK_KEY			113
# define HELP_CHALK			114
# define HELP_KEY			115
# define REPLACE			116
/* Animation constants */
# ifndef M_PI
#  define M_PI			3.14159265358979323846

# endif

/* ************************************************************************** */
/*                                ENUMS                                     */
/* ************************************************************************** */

typedef enum e_wall_dir
{
	NORTH	= 0,
	SOUTH	= 1,
	EAST	= 2,
	WEST	= 3
}					t_wall_dir;

typedef enum e_door_state
{
	DOOR_CLOSED = 0,
	DOOR_OPEN	= 1
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
	int				l_height;
	int				d_start;
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
	float			angle;
	float			step;
	float			tx_pos;
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
	float			pitch;
	char			*orientation;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			left_rot;
	bool			key_right;
	bool			right_rot;
	bool			pitch_up;
	bool			pitch_down;
	bool			key_run;
	int				mouse_x;
	int				mouse_y;
	bool			key_f_pressed;
}					t_player;

typedef struct s_texture
{
	void			*img;
	char			*name;
	int				l_height;
	int				d_start;
	int				draw_end;	
	int				*data;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	int				bpp;
	int				x;
	int				y;
}					t_text;

typedef struct s_door
{
	int				x;
	int				y;
	char			type;
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
	int				d_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				d_start_x;
	int				draw_end_x;
}					t_sprite;

typedef struct s_chalk_sprite
{
	void			*img;
	int				*data;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	char			type;
	double			x;
	double			y;
	double			base_x;
	double			base_y;
	double			time;
	double			amplitude;
	double			frequency;
	int				visible;
	int				collected;
	int				id;
}					t_chalk_sprite;

typedef struct s_bounds
{
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}					t_bounds;

typedef struct s_draw_params
{
	int				x;
	int				y;
	int				start_x;
	int				start_y;
	int				sprite_width;
	int				sprite_height;
}					t_draw_params;

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

typedef struct s_ray_table
{
	float			ray_angles[WIDTH];
	float			ray_cos[WIDTH];
	float			ray_sin[WIDTH];
	bool			initialized;
}					t_ray_table;

typedef struct s_game
{
	int				print_flag;
	int				random_flag;
	int				stop;
	int				y;
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
	int				item_count;
	float			random_x;
	float			random_y;
	char			**inventory;
	char			orientation;
	char			*current_line;
	char			**map;
	char			*data;
	void			*mlx;
	void			*win;
	void			*img;
	float			*z_buffer;
	float			arm_offset;
	float			bob_intensity;
	float			spawn_x;
	float			spawn_y;
	float			bob_time;
	float			fov;
	float			darken_factor;
	pthread_t		thread;
	pthread_mutex_t	fov_lock;
	pthread_mutex_t	darken_lock;
	t_door			*doors;
	t_sprite		*sprite_list;
	t_player		player;
	t_minimap		minimap;
	t_text			screen_over;
	t_text			screen_win;
	t_text			north;
	t_text			south;
	t_text			east;
	t_text			west;
	t_text			mirror;
	t_text			char_mirror;
	t_text			left_arm;
	t_text			right_arm;
	t_text			right_chalk;
	t_text			north_chalk;
	t_text			south_chalk;
	t_text			east_chalk;
	t_text			west_chalk;	
	t_text			character;
	t_text			door;
	t_text			exit;
	t_chalk_sprite	*chalk_sprites;
	int				chalk_sprite_count;
	int				chalk_collected;
	bool			minimap_toggle;
	double			game_time;
	t_text			*sprites;
	t_ray_table		ray_table;
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
void				ft_free_wall_textures(t_game *game);
void				close_with_print(t_game *game, char *to_print);

/* ****************************************************************************/
/*                              PARSER                                        */
/* ****************************************************************************/

void				validate_content(char **map, t_game *game,
						t_list **map_lines);
void				validate_boundaries(char **map, t_game *game,
						t_list **map_lines);
void				validate_chars_and_count(char **map, int *player_count,
						t_game *game, t_list **map_lines);
void				fetch_player_cords(char **map, t_game *game);
int					store_doors(char **map, t_game *game);

/* ****************************************************************************/
/*                              INITIALIZATION                                */
/* ****************************************************************************/

void				init_game(t_game *game);
int					game_init(t_game *game);
void				init_game_vars(t_game *game);
short				load_texture(t_game *game, t_text *texture, char *path);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
void				handle_movement_keys(int keycode, t_player *player);
void				handle_view_keys(int keycode, t_player *player);
void				handle_action_keys(int keycode, t_game *game,
						t_player *player);
void				cleanup_game(t_game *game);
int					close_game(t_game *game);
int					mouse_move(int x, int y, t_game *game);
void				setup_chalk_sprite(t_game *game, int row, int col, int idx);

/* ****************************************************************************/
/*                              GAME LOOP                                     */
/* ****************************************************************************/

void				game_loop(t_game *game);
void				move_player(t_player *player, t_game *game);
void				move_player_keys(t_player *player, t_game *game);
bool				is_wall(t_game *game, float x, float y);
void				update_arm_bobbing(t_game *game);
void				draw_image_with_transparency(t_game *game, t_text *src,
						int x, int y);
void				render_game_arms(t_game *game);
void				print_handler(t_game *game, t_player *player);

/* ****************************************************************************/
/*                              RENDERING                                     */
/* ****************************************************************************/

void				draw_pixel(int x, int y, int color, t_game *game);
void				clear_image(t_game *game);
void				draw_line(t_player *player, t_game *game, float ray_angle,
						int screen_x);
void				ray_init(t_ray *ray, t_player *player, float ray_angle);
void				dda_finder(t_ray *ray, t_game *game);
void				distance_wall(t_ray *ray, t_player *player);
void				texture_cord(t_ray *ray, t_player *player, t_text *text);
void				vertical_texture(t_ray *ray, t_text *text);
void				ceiling_render(t_ray *ray, t_game *game, int screen_x);
void				wall_render(t_ray *ray, t_text *text, t_game *game,
						int screen_x);
void				floor_render(t_ray *ray, t_game *game, int screen_x);
void				draw_image_with_transparency(t_game *game, t_text *src,
						int x, int y);
int					dim_color(int color, float factor);
float				factor_calculator(t_ray *ray, t_game *game);
void				draw_line_fast(t_player *player, t_game *game,
						t_ray_table *table, int screen_x);

/* ****************************************************************************/
/*                              MINIMAP                                       */
/* ****************************************************************************/

void				init_minimap(t_game *game);
void				draw_minimap(t_game *game);
void				draw_minimap_player(t_game *game);
void				draw_minimap_walls(t_game *game);
void				put_pixel_minimap(t_game *game, int x, int y, int color);
void				recreate_minimap_image(t_game *game, int width, int height);
void				blend_pixel_colors(t_game *game, int x, int y);
void				clear_minimap_properly(t_game *game);
void				composite_minimap_to_main(t_game *game);
void				minimap_toggle(t_game *game);

/* ****************************************************************************/
/*                              INTERACTIONS                                  */
/* ****************************************************************************/

void				init_doors(t_game *game);
void				interact_door(t_game *game);
bool				is_door(char c);
void				wall_tag(t_player *player, t_game *game);
void				pick_up_item(t_player *player, t_game *game);
int					has_item(t_game *game, char *to_find);
void				*thread(void *arg);
int					is_close_enough(t_game *game, t_player *player,
						char to_find);
bool				teleport_check(t_game *game, float x, float y);
void				add_to_inv(t_game *game, char *item);
int					remove_from_inv(t_game *game, char *to_remove);
void				perform_move(t_game *game, float x_offset, float y_offset);
bool				check_tile_collision(t_game *game, int map_x, int map_y);
double				delta_calculator(void);

/* ****************************************************************************/
/*                               MIRROR                                       */
/* ****************************************************************************/

void				reflection(t_ray *ray, t_game *game, int screenX);
void				mirror_texture(t_game *game, t_ray *ray, t_text *text,
						int screenX);
t_text				*choose_mirror_texture(t_ray *ray, t_game *game,
						float nx, float ny);

/* ****************************************************************************/
/*                               TIME                                         */
/* ****************************************************************************/

long				get_timestamp_ms(long start_time);
long				get_start_time(void);

/* ****************************************************************************/
/*                              CHALK SPRITES                                */
/* ****************************************************************************/

int					parse_map_for_chalks(t_game *game);
int					init_chalk_sprite_system(t_game *game);
int					load_chalk_sprite_texture(t_game *game,
						t_chalk_sprite *sprite);
void				animate_chalks(t_game *game, double delta_time);
void				animate_chalk_sprite(t_chalk_sprite *sprite,
						double delta_time);
void				render_chalks(t_game *game);
void				render_chalk_sprite(t_game *game, t_chalk_sprite *sprite);
bool				is_chalk_visible(t_game *game, t_chalk_sprite *sprite);
void				cleanup_chalk_sprites(t_game *game);
double				get_current_time(void);
double				normalize_angle(double angle);
int					is_in_fov(t_game *game, double sprite_x, double sprite_y);
void				draw_chalks_on_minimap(t_game *game);
void				calc_screen_pos(t_game *game, t_chalk_sprite *sprite,
						int *screen_x, double *distance);
void				calc_sprite_size(double distance, int *width, int *height);
int					chalk_count_in_inventory(t_game *game);
void				ray_handler(t_ray *ray);
void				check_chalk_sprites(t_game *game, t_player *player);

/* ****************************************************************************/
/*                              TEXTURES                                      */
/* ****************************************************************************/

short				wall_textures(t_game *game);
short				texture_init(t_game *game);

#endif
