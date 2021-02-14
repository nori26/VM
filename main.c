#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159265

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello world!");
    img.img = mlx_new_image(mlx, 1000, 1000);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("%d\n", img.line_length);
    int x = 0;
    int y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
			my_mlx_pixel_put(&img, 100 + x++, 100 + y, 0x0000FF00);
		y++;
	}
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < y / sin(PI/3))
			my_mlx_pixel_put(&img, 300 - y / (2 * sin(PI/3)) + x++, 100 + y, 0x00FF0000);
		y++;
	}
	y = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 2 * sqrt(2500 - pow(50 - y, 2)))
			my_mlx_pixel_put(&img, 450 - sqrt(2500 - pow(50 - y, 2)) + x++, 100 + y, 0x000000FF);
		y++;
	}
	while (y < 100)
	{
		x = 0;
		while (x < 2 * sqrt(2500 - pow(y - 50, 2)))
			my_mlx_pixel_put(&img, 450 - sqrt(2500 - pow(y - 50, 2)) + x++, 100 + y, 0x000000FF);
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}