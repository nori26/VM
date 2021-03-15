#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_pic {
    void        *img;
    char        *addr;
    int         bpp;
    int         width_bytes;
    int         endian;
	void		*mlx;
	void		*win;
}               t_pic;
void            pixel_put(t_pic *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->width_bytes + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_pic  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.width_bytes,
								&img.endian);
	int i = 0;
	int j = 0;
	while (j < 100)
	{
		i = 0;
		while (i < j)
			pixel_put(&img, 100 / 2 - j / 2 + 5 + i++, 5 + j, 0x00FF0000);
		j++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}