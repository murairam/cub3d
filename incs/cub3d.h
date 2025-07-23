#ifndef CUB3D_H
#define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"


# include "parser.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_game{
    char **map; 
    int fd;
    char *tex_N;
    char *tex_S;
    char *tex_E;
    char *tex_W;
    char *tex_F;
    int    color_c;
    int    color_f;
}   t_game;


// UTILS
int ft_error(const char *msg);
void ft_exit_error(const char *msg);
void ft_free_split(char **split);
void ft_free_game(t_game *game);
void ft_exit_error_with_cleanup(t_game *game, const char *msg);
void ft_exit_error_with_cleanup_and_list(t_game *game, t_list **map_lines, const char *msg);

#endif