#include "mlx.h"
#include "puts.h"

void draw(t_img *img, int width, int height)
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

void	draw_img(t_img *img)
{
	int 	color;
	int		x;
	int		y;
	double	t;
	t_vect	pos;

	y = 0;
	color = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			img->lst = img->start;
			pos = point_to_vect(x, y, *img);
			img->view = vect_unit(vect_sub(pos, img->cam));
			ft_bzero(&img->point, sizeof(img->point));
			while (img->lst)
			{
				t = img->lst->f(img, img->lst->obj);
				img->lst = img->lst->next;
			}
			if (t)
			{
				color = light(img);
				if (color > 255)
					color = 255;
				my_mlx_pixel_put(img, x, y, (color << 16) + ((int)(color * 0.4) << 8) + (int)(color * 0.4));
			}
			else
				my_mlx_pixel_put(img, x, y, (100 << 16) + (149 << 8) + 237);
			x++;
		}
		y++;
	}
}

int	sp_init(t_img *img, double (*f)(), t_vect o, double r)
{
	t_sp *sp;

	if (!(sp = malloc(sizeof(t_sp))))
		return (-1);
	sp->o = o;
	sp->r = r;
	if (!ft_lstadd_front(img->lst, ft_lstnew(sp, sphere)))
		return (-1);
	return (0);
}

void light_init(t_img *img, t_vect l)
{
	img->light.pos = l;
}

void	calc(t_img img)
{
	sp_init(&img, sphere, vect_init(0, 0, 5), 1);
	light_init(&img, vect_init(-5, 5, -5));
	img.cam = vect_init(0, 0, -5);
	img.start = img.lst;
	draw_img(&img);
}

int     main(void)
{
	t_vect	v;
	t_img  img;

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
