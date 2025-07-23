#include "incs/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (ft_printf("Usage: ./cub3D maps/map.cub\n"), 1);

    if (!parse_file(argv[1], &game))
        return (ft_error("parsing failed\n"));

    // // Test output
    // printf("Map:\n");
    // for (int i = 0; game.map[i]; i++)
    //     printf("%s\n", game.map[i]);
    // printf("North texture: %s\n", game.north_tex);
    // printf("Floor color: %d\n", game.floor_color);

    return (0);
}
