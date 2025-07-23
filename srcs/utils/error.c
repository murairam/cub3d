#include "cub3d.h"

int ft_error(const char *msg)
{
    write(2, "Error: ", 7);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    return (0);
}
