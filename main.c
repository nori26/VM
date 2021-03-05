/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:55:51 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/05 10:14:17 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "puts.h"

t_vect	camera(t_img *img, int x, int y)
{
	double a;
	double b;
	t_vect center;
	t_vect v_x;
	t_vect v_y;
	t_vect u_x;
	t_vect u_y;
	t_vect view;

	center = img->cam->cent;
	if (img->cam->n.x && img->cam->n.y)
	{
		a = -center.y / sqrt(center.x * center.x + center.z * center.y);
		b = center.x / sqrt(center.x * center.x + center.z * center.y);
		u_x = vect_init(a, b, 0);
		u_y = vect_unit(cross(u_x, center));
		v_x = vect_mult(u_x, x - img->w / 2);
		v_y = vect_mult(u_y, y - img->h / 2);
		view = vect_add(vect_sub(v_x, v_y), center);
		if (!x && !y)
			printf("len %f\n", vect_len(center));
		view = vect_unit(view);
	}
	else
	{
		u_x = vect_init(1, 0, 0);
		u_y = vect_unit(cross(u_x, center));
		v_x = vect_mult(u_x, x - img->w / 2);
		v_y = vect_mult(u_y, y - img->h / 2);
		view = vect_add(vect_sub(v_x, v_y), center);
		// if (!x && !y)
		// 	printf("dot1 : %f\ndot2 : f\ndot3 : f\n", dot(center, v_x), dot(center, v_y), dot(v_y, v_x));
		view = vect_unit(view);
	}
	if (!x && !y)
	{
		printf("x.x : %f\nx.y : %f\nx.z : %f\n", v_x.x,  v_x.y, v_x.z);
		printf("root : %f\n", sqrt(center.x * center.x + center.y * center.y));
		printf("xlen : %f\nylen : %f\n", vect_len(v_x), vect_len(v_y));
		printf("centlen : %f\n", vect_len(center));
	}
	// printf("%f\n", vect_len(view));
	// if (!x && !y)
		// printf("dot1 : %f\ndot2 : %f\ndot3 : %f\n", dot(center, v_x), dot(center, v_y), dot(v_y, v_x));
		// printf("dot1 : %f\ndot2 : %f\n", vect_len(u_x),vect_len(u_y));
	return (view);
}

void	draw_img(t_img *img, t_clist cam)
{
	int		x;
	int		y;
	t_vect	pos;

	(void)cam;
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			img->lst = img->o_start;
			pos = vect_init(2.0 * x / (img->w - 1) - 1,
							-2.0 * y / (img->h - 1) + 1, 0);
			img->view = camera(img, x, y);
			img->view = vect_unit(vect_sub(pos, cam.pos));
			ft_bzero(&img->node, sizeof(img->node));
			img->node.pos_len = -1;
			while (img->lst)
			{
				if (!x && !y)
					printf("%d\n", 1);
				img->lst->f(img, img->lst->obj);
				img->lst = img->lst->next;
			}
			if (img->node.pos_len != -1)
			{
				my_mlx_pixel_put(img, x, y,
							color(img->node.rgb, *img->light, light(img)));
			}
			else
				my_mlx_pixel_put(img, x, y, (50 << 8) + 100);
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
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_o(sp, sphere)))
		return (-1);
	return (0);
}

void light_init(t_img *img, t_vect l)
{
	t_llist light;
	light.pos = l;
	light.rgb = rgb_init(255, 255, 255);
	light.pow = 1;
	img->light = ft_lstnew_l(light);
}

void	screen_center(t_img *img)
{
	double distance;

	distance = img->w / (2 * tan(img->cam->fov / 2));
	img->cam->cent = vect_mult(img->cam->n, distance);
	printf("dist : %f\n", distance);
}

void	calc(t_img *img)
{
	if (!img->lst)
	{
		// sp_init(img, vect_init(3, 0, 25), 1, rgb_init(255, 0, 0));
		// sp_init(img, vect_init(2, 0, 20), 1, rgb_init(0, 255, 0));
		// sp_init(img, vect_init(1, 0, 15), 1, rgb_init(0, 0, 255));
		// sp_init(img, vect_init(0, 0, 10), 1, rgb_init(255, 255, 255));
		// sp_init(img, vect_init(-1, 0, 5), 1, rgb_init(255, 0, 0));
		sp_init(img, vect_init(0, 0, 5), 1, rgb_init(255, 0, 0));
		// printf("aaa\n");
		light_init(img, vect_init(-5, 5, -5));
		// light_init(img, vect_init(150, 150, -150));
		// img->cam = vect_init(0, 0, -30);
		img->o_start = img->lst;
	}
	t_sp *sp;
	sp = img->lst->obj;
	printf("o : %f %f %f\n", sp->o.x, sp->o.y, sp->o.z);
	printf("r ; %f\n", sp->r);
	while (img->cam)
	{
		screen_center(img);
		draw_img(img, *img->cam);
		img->cam = img->cam->next;
	}
	img->cam = img->c_start;
}

void		make_img(t_img *img)
{
	int w = 0;
	int h = 0;

    img->mlx = mlx_init();
	printf("%d\n%d\n", img->w, img->h);
	img->win = mlx_new_window(img->mlx, img->w, img->h, "miniRT");
	img->img = mlx_new_image(img->mlx, img->w, img->h);
	img->cam->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	mlx_get_screen_size(img->mlx, &w, &h);
	img->w = img->w > w ? w : img->w;
	img->h = img->h > h ? h : img->h;
	printf("%d\n%d\n", w, h);
	calc(img);
	mlx_hook(img->win, 2, 1, close2, img);
	mlx_hook(img->win, 33, 1 << 17, close1, img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
    mlx_loop(img->mlx);
}

int     main(int argc, char *argv[])
{
	t_img 	img;

	if (argc < 2 || argc > 3)
		return (0);
	ft_bzero(&img, sizeof(img));
	if (argc > 2 && !(img.bmp += !ft_strncmp(argv[2], "--save", 7)))
		return 0;
	read_rt(&img, argv[1]);
	make_img(&img);
}
