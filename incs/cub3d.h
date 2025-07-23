#ifndef CUB3D_H
#define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "parser.h"

typedef struct s_game{
    char **map; 
    int fd;
}   t_game;


// UTILS
int ft_error(const char *msg);

#endif