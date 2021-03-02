/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:55:51 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/26 08:23:47 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "puts.h"

void	draw_img(t_img *img)
{
	int		x;
	int		y;
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
			ft_bzero(&img->node, sizeof(img->node));
			img->node.pos_len = -1;
			while (img->lst)
			{
				img->lst->f(img, img->lst->obj);
				img->lst = img->lst->next;
			}
			if (img->node.pos_len != -1)
			{
				my_mlx_pixel_put(img, x, y,
							color(img->node.rgb, img->light, light(img)));
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
	return (color);
}

int	sp_init(t_img *img, t_vect o, double r, t_rgb rgb)
{
	t_sp	*sp;

	if (!(sp = malloc(sizeof(t_sp))))
		return (-1);
	sp->o = o;
	sp->r = r;
	sp->rgb = rgb;
	if (!ft_lstadd_front_rt(&img->lst, ft_lstnew_rt(sp, sphere)))
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
	sp_init(img, vect_init(3, 0, 25), 1, rgb_init(255, 0, 0));
	sp_init(img, vect_init(2, 0, 20), 1, rgb_init(0, 255, 0));
	sp_init(img, vect_init(1, 0, 15), 1, rgb_init(0, 0, 255));
	sp_init(img, vect_init(0, 0, 10), 1, rgb_init(255, 0, 0));
	sp_init(img, vect_init(-1, -0, 5), 1, rgb_init(0, 255, 0));
	// sp_init(img, vect_init(0, 0, 30), 10, rgb_init(255, 0, 0));
	light_init(img, vect_init(30, 30, -30));
	// light_init(img, vect_init(150, 150, -150));
	img->cam = vect_init(0, 0, -5);
	// img->cam = vect_init(0, 0, -30);
	img->start = img->lst;
	draw_img(img);
}

int     main(void)
{
	t_img  img;

	ft_bzero(&img, sizeof(img));
	img.w = 1920;
	img.h = 975;
    img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.w, img.h, "Hello world!");
	img.img = mlx_new_image(img.mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	int x = 0;
	int y = 0;
	mlx_get_screen_size(img.mlx, &x, &y);
	printf("%d\n%d\n", x, y);
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
