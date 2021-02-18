#include "mlx.h"
#include "puts.h"
#include <math.h>

void draw(t_data *img, int width, int height)
{
	int x = 0;
	int y = 0;
	int color = 0;
	int count = width / 255 + !!(width % 255);
	int i;
	double fx;
	double fy;

	while (y < height)
	{
		i = 0;
		x = 0;
		fy = (double)y / (height -1);
		while (x < width)
		{
			fx = (double)x / (width -1);
			color = (int)(255 * (1 - fx)) << 16;
			color |= (int)(255 * fy) << 8;
			color |= (int)(255 * fx * fy);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
	// printf("%d\n", 0xff);
}


int     main(void)
{
	t_vec	v;
	t_data  img;
    int     img_w;
    int     img_h;
	int		w = 512;
	int		h = 512;

	v.z = 0;
    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, w, h, "Hello world!");
	img.img = mlx_new_image(img.mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	// img.img = mlx_xpm_file_to_image(img.mlx, "./test.xpm", &img_width, &img_height);
    // mlx_loop_hook(img.mlx, render_next_frame, &img);
	v.x = 2 * w / (img_w - 1) - 1;
	v.y = -2 * h / (img_h - 1) - 1;
	draw(&img, w, h);
	mlx_hook(img.win, 2, 1L << 0, close2, &img);
	mlx_hook(img.win, 33, 1L << 17, close1, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
