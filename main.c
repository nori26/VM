#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	void		*mlx;
	void		*win;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     render_next_frame(t_data *img)
{
	static int i = 0;

	if (i < 800)
	{
		my_mlx_pixel_put(img, i, i, 0x00FF0000);
		my_mlx_pixel_put(img, i + 1, i, 0x00FF0000);
		my_mlx_pixel_put(img, i + 2, i, 0x00FF0000);
		my_mlx_pixel_put(img, i + 3, i, 0x00FF0000);
		my_mlx_pixel_put(img, i + 4, i, 0x00FF0000);
		my_mlx_pixel_put(img, i + 5, i, 0x00FF0000);
		my_mlx_pixel_put(img, i + 6, i, 0x00FF0000);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
		i++;
	}
	printf("%d\n", i);
	return (0);
}
int             close1(int keycode, t_data *vars)
{
    // mlx_destroy_window(vars->mlx, vars->win);
	// mlx_destroy_display(vars->mlx);
	exit(0);
}

int             close2(int keycode, t_data *vars)
{
	printf("%d\n", keycode);
    if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}
int     main(void)
{
	t_data  img;
    int     img_width;
    int     img_height;

    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 800, 800, "Hello world!");
	img.img = mlx_new_image(img.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                            &img.endian);
	mlx_hook(img.win, 33, 1L<<17, close1, &img);
	mlx_hook(img.win, 2, 1L<<0, close2, &img);
	img.img = mlx_xpm_file_to_image(img.mlx, "./test.xpm", &img_width, &img_height);
    // mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
// int             main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_data  img;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//     img.img = mlx_new_image(mlx, 1920, 1080);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//                                  &img.endian);
// 	int i = 0;
// 	int j = 0;
// 	while (j < 100)
// 	{
// 		i = 0;
// 		while (i < 100)
// 		    my_mlx_pixel_put(&img, 5 + i++, 5 + j, 0x00FF0000);
// 		j++;
// 	}
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 100, );
//     mlx_loop(mlx);
// }