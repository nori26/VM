#include "mlx.h"
#include "puts.h"

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
}

void	draw_img(t_data *img, t_vect sp, t_vect cam, int i)
{
	int		x;
	int		y;
	int 	color = 0;
	double	t;
	double	r = 1;
	t_vect	pos;
	t_vect	u_view;
	t_vect	p_point;

	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			pos = point_to_vect(x, y, *img);
			// if (x == 128 && y == 255)
			// {
			u_view = vect_unit(vect_sub(pos, cam));
			// printf("%f\n", ray.len);
			// printf("%f\n%f\n%f\n", pix.x, pix.y, pix.z);
			// printf("%f\n%f\n%f\n%f\n", ray.x, ray.y, ray.z, ray.len);
			if ((t = sphere(cam, u_view, sp, r)) && i)
			{
				p_point = vect_add(vect_mult(u_view, t), cam);
				// if (x == 255 && y == 255){					
					color = light(p_point, sp, u_view);
					if (color > 255)
						color = 255;
					// printf("%d\n%f\n", color, t);//}
				my_mlx_pixel_put(img, x, y, (color << 16) + ((int)(color * 0.4) << 8) + (int)(color * 0.4));
			}
			if (!i)
				my_mlx_pixel_put(img, x, y, (100 << 16) + (149 << 8) + 237);
			// }
			x++;
		}
		y++;
	}
}

void	calc(t_data img)
{
	t_vect	cam;
	t_vect	sp;
	t_vect	ray;

	draw_img(&img, sp, cam, 0);
	cam = vect_init(0, 0, -5);

	sp = vect_init(3, 0, 25);
	draw_img(&img, sp, cam, 1);
	sp = vect_init(2, 0, 20);
	draw_img(&img, sp, cam, 1);
	sp = vect_init(1, 0, 15);
	draw_img(&img, sp, cam, 1);
	sp = vect_init(0, 0, 10);
	draw_img(&img, sp, cam, 1);
	sp = vect_init(-1, 0, 5);
	draw_img(&img, sp, cam, 1);
}

int     main(void)
{
	t_vect	v;
	t_data  img;

	img.w = 512;
	img.h = 512;
    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.w, img.h, "Hello world!");
	img.img = mlx_new_image(img.mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	// mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	// img.img = mlx_xpm_file_to_image(img.mlx, "./test.xpm", &img_width, &img_height);
    // mlx_loop_hook(img.mlx, render_next_frame, &img);
	// printf("%d\n", img.line_length / 4);
	calc(img);
	mlx_hook(img.win, 2, 1L << 0, close2, &img);
	mlx_hook(img.win, 33, 1L << 17, close1, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
