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

t_vect	vect_init(double x, double y, double z)
{
	t_vect ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.len = vect_len(ret);
	return (ret);
}

void	draw_img(t_data img, t_vect sp, t_vect cam, t_win win)
{
	int x = 0;
	int y = 0;
	t_vect ray;

	while (y < win.h)
	{
		x = 0;
		while (x < win.w)
		{

			my_mlx_pixel_put(img, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	calc()
{
	t_vect	cam;
	t_vect	sp;
	t_vect	ray;

	cam = vect_init(0, 0, -5);
	sp = vect_init(0, 0, 5);
	ray = vect_sub(, cam);
	ray.len = vect_len(d);

}

int     main(void)
{
	t_vect	v;
	t_data  img;
	t_win	win;

	win.w = 512;
	win.h = 512;
	img.w = win.w;
	img.h = win.h;
    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, win.w, win.h, "Hello world!");
	img.img = mlx_new_image(img.mlx, win.w, win.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	// img.img = mlx_xpm_file_to_image(img.mlx, "./test.xpm", &img_width, &img_height);
    // mlx_loop_hook(img.mlx, render_next_frame, &img);
	printf("%d\n", img.line_length / 4);
	draw(&img, win.w, win.h);
	mlx_hook(img.win, 2, 1L << 0, close2, &img);
	mlx_hook(img.win, 33, 1L << 17, close1, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
