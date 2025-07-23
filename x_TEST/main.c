#include "mlx.h"

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "cub3D test");
    void *img = mlx_new_image(mlx, 800, 600);
    int *data = (int *)mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});

    // Set one pixel in the center to red
    data[300 * 800 + 400] = 0x00FF0000;

    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
}

