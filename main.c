/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:55:51 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/24 22:37:39 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "puts.h"

int		color(t_rgb obj, t_light light, double ref)
{
	int r;
	int g;
	int b;

	r = 255 * obj.r * light.rgb.r * ref;
	g = 255 * obj.g * light.rgb.g * ref;
	b = 255 * obj.b * light.rgb.b * ref;
	return ((r << 16) + (g << 8) + b);
}

void	draw_img(t_img *img)
{
	int		x;
	int		y;
	double	t;
	t_vect	pos;

	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			img->lst = img->start;
			pos = vect_init(2.0 * x / (img->w - 1) - 1,
							-2.0 * y / (img->h - 1) + 1, 0);
			img->view = vect_unit(vect_sub(pos, img->cam));
			ft_bzero(&img->point, sizeof(img->point));
			img->point.pos_len = -1;
			while (img->lst->next)
			{
				img->lst->f(img, img->lst->obj);
				img->lst = img->lst->next;
			}
			img->lst->f(img, img->lst->obj);
			if (img->point.pos_len > -1)
			{
				my_mlx_pixel_put(img, x, y, color(img->lst->rgb, img->light, light(img)));
			}
			else
				my_mlx_pixel_put(img, x, y, (100 << 16) + (149 << 8) + 237);
			x++;
		}
		y++;
	}
}

t_rgb	rgb_init(int r, int g, int b)
{
	t_rgb color;

	color.r = r / 255.0;
	color.g = g / 255.0;
	color.b = b / 255.0;
	printf("%f\n", color.r);
	return (color);
}

int	sp_init(t_img *img, double (*f)(), t_vect o, double r)
{
	t_sp	*sp;
	t_rgb	rgb;

	if (!(sp = malloc(sizeof(t_sp))))
		return (-1);
	sp->o = o;
	sp->r = r;
	rgb = rgb_init(255, 0, 0);
	if (!ft_lstadd_front(&img->lst, ft_lstnew(sp, sphere, rgb)))
		return (-1);
	return (0);
}

void light_init(t_img *img, t_vect l)
{
	img->light.pos = l;
	img->light.rgb = rgb_init(255, 255, 255);
}
void	calc(t_img *img)
{
	sp_init(img, sphere, vect_init(0, 0, 5), 1);
	sp_init(img, sphere, vect_init(0, 15, 5), 1);
	sp_init(img, sphere, vect_init(0, 20, 5), 1);
	light_init(img, vect_init(-5, 5, -5));
	img->cam = vect_init(0, 0, -5);
	img->start = img->lst;
	draw_img(img);
}

int     main(void)
{
	t_vect	v;
	t_img  img;

	ft_bzero(&img, sizeof(img));
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
	calc(&img);
	mlx_hook(img.win, 2, 1L << 0, close2, &img);
	mlx_hook(img.win, 33, 1L << 17, close1, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
