#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define TILE_SIZE 70
#define WIN_WIDTH 640
#define WIN_HEIGHT 480

// Sample map (you'll replace this later with your .cub parser output)
char *sample_map[] = {
    "1111111111",
    "1000000001",
    "1000010001",
    "1000N10001",
    "1000000001",
    "1111111111",
    NULL
};

void draw_square(void *mlx, void *win, int x, int y, int color)
{
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            mlx_pixel_put(mlx, win, x + j, y + i, color);
        }
    }
}

void draw_map(void *mlx, void *win, char **map)
{
    int row = 0;
    while (map[row])
    {
        int col = 0;
        while (map[row][col])
        {
            int x = col * TILE_SIZE;
            int y = row * TILE_SIZE;

            if (map[row][col] == '1')
                draw_square(mlx, win, x, y, 0xFFFFFF); // white wall
            else if (map[row][col] == '0')
                draw_square(mlx, win, x, y, 0x000000); // black floor
            else if (map[row][col] == 'N' || map[row][col] == 'S'
                  || map[row][col] == 'E' || map[row][col] == 'W')
                draw_square(mlx, win, x, y, 0x00FF00); // green player
            else
                draw_square(mlx, win, x, y, 0xAAAAAA); // undefined = gray
            col++;
        }
        row++;
    }
}

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
    {
        fprintf(stderr, "Error: Could not initialize MiniLibX\n");
        return (1);
    }

    win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D - 2D Map Viewer");
    if (!win)
    {
        fprintf(stderr, "Error: Could not create window\n");
        return (1);
    }

    draw_map(mlx, win, sample_map);

    mlx_loop(mlx);
    return (0);
}
