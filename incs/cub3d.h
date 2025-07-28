#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                INCLUDES                                   */
/* ************************************************************************** */

# include 	"libft/libft.h"
# include 	"mlx/mlx.h"
# include 	"mlx/mlx_int.h"
# include 	"parser.h"
# include 	<fcntl.h>
# include	<stdio.h>
# include	<stdbool.h>
# include 	<stdlib.h>
# include 	<unistd.h>
# include	<math.h>

/* ************************************************************************** */
/*                                DEFINES                                   */
/* ************************************************************************** */

# define BIG_FLOAT  1e30f
# define PI		    3.14159265359
# define WIDTH	    1280
# define HEIGHT	    720
# define CUBE	    64
# define LEFT	    65361
# define RIGHT	    65363
# define W		    119
# define A		    97
# define S		    115
# define D		    100

/* ************************************************************************** */
/*                                DEFINES                                   */
/* ************************************************************************** */

typedef enum e_wall_dir
{
    NORTH = 0,
    SOUTH = 1,
    EAST  = 2,
    WEST  = 3
}   t_wall_dir;

/* ************************************************************************** */
/*                                STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_ray
{
    char    *pixel;
    int     lineHeight;
    int     drawStart;
    int     drawEnd;
    int     texPos;
    int     color;
    int     stepX;
    int     stepY;
    int     mapX;
    int     mapY;
    int     side;
    int     texX;
    int     texY;
    int     step;
    int     hit;
    float   wallX;
    float   rayDirX;
    float   rayDirY;
    float   deltaDistY;
    float   deltaDistX;    
    float   sideDistX;
    float   sideDistY;
    float   perpWallDist;
}   t_ray;


typedef struct s_player
{
    float   x;
    float   y;
    float   angle;
    bool    key_up;
    bool    key_down;
    bool    key_left;
    bool    left_rot;
    bool    key_right;
    bool    right_rot;
}   t_player;

typedef struct s_texture
{
    void    *img;
    char    *name;
    int     *data;
    int     size_line;
    int     endian;
    int     width;
    int     height;
    int     bpp;
}   t_texture;

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
    t_player	player;
    t_texture	north;
    t_texture	south;
    t_texture	east;
    t_texture	west;
}			t_game;


/* ************************************************************************** */
/*                              ERROR HANDLING                               */
/* ************************************************************************** */

int		ft_error(const char *msg);
void	ft_exit_error(const char *msg);
void	ft_exit_error_with_cleanup(t_game *game, const char *msg);

/* ************************************************************************** */
/*                              MEMORY MANAGEMENT                            */
/* ************************************************************************** */

void	ft_free_split(char **split);
void	ft_free_game(t_game *game);

/* ************************************************************************** */
/*                              INITIALIZATION                               */
/* ************************************************************************** */

void	init_game(t_game *game);
int     game_init(t_game *game);
int     key_press(int keycode, t_player *player);
int     key_release(int keycode, t_player *player);

/* ************************************************************************** */
/*                              GAME LOOP                               */
/* ************************************************************************** */

void    game_loop(t_game *game);
void    move_player(t_player *player);
void    move_player_keys(t_player *player, float cos_angle, float sin_angle, int speed);

/* ************************************************************************** */
/*                              RENDERING                               */
/* ************************************************************************** */

void    put_pixel(int x, int y, int color, t_game *game);
void    clear_image(t_game *game);
void    draw_line(t_player *player, t_game *game, float rayAngle, int screenX);


#endif