/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:55:51 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/10 08:50:30 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "puts.h"

t_vect	camera(t_img *img, int x, int y)
{
	t_vect v_x;
	t_vect v_y;
	t_vect u_x;
	t_vect u_y;
	t_vect center;

	center = img->cam->cent;
	if (!img->cam->n.x && !img->cam->n.z)
		u_x = vect_init(1, 0, 0);
	else
	{
		u_x = vect_init(
			center.z / sqrt(center.x * center.x + center.z * center.z),
			0,
			-center.x / sqrt(center.x * center.x + center.z * center.z));
	}
	u_y = vect_unit(cross(u_x, vect_mult(center, -1)));
	v_x = vect_mult(u_x, x - img->w / 2);
	v_y = vect_mult(u_y, img->h / 2 - y);
	img->u_view = vect_unit(vect_add(vect_add(v_x, v_y), center));
	return (img->u_view);
}

void	screen_center(t_img *img)
{
	double distance;

	distance = img->w / (2 * tan(img->cam->fov / 2));
	img->cam->cent = vect_mult(img->cam->n, distance);
	printf("dist : %f\n", distance);
}

int i;
void		shadow(t_img *img)
{
	double dist;
	double dist_from_light;
	t_vect u_shadow_ray;
	t_vect ray_start;

	dist= -1;
	img->shad = 1;
	img->light = img->l_start;
	while (img->light)
	{
		u_shadow_ray = vect_unit(vect_sub(img->light->pos, img->node.pos));
		ray_start = vect_add(img->node.pos, vect_mult(u_shadow_ray, EPSILON));
		dist_from_light = vect_len(vect_sub(img->light->pos, ray_start));
		img->ray_start = ray_start;
		img->lst = img->o_start;
		while ((img->lst))
		{
			dist = img->f_node_judge[img->lst->id]
				(img, img->lst->obj, u_shadow_ray,
				img->f_ret_to_raystart[img->lst->id](img->lst->obj, ray_start));
			printf("dist   %f\n",dist);
			if (dist != -1 && dist < dist_from_light)
			{
				img->light->on = OFF;
				break ;
			}
			img->lst = img->lst->next;
		}
		img->light = img->light->next;
	}
	img->shad = 0;
}

void		node_judge(t_img *img)
{
	double dist;

	img->lst = img->o_start;
	while ((img->lst))
	{
		dist = img->f_node_judge[img->lst->id]
			(img, img->lst->obj, img->u_view,
			img->f_ret_to_cam[img->lst->id](img->lst->obj));
		if (dist != -1 && (img->node.dist == -1 || (dist < img->node.dist)))
			img->f_update_node[img->lst->id](img, dist, img->lst->obj);
		img->lst = img->lst->next;
	}
}

void	object_to_cam(t_img *img)
{
	img->lst = img->o_start;
	while (img->lst)
	{
		img->f_to_cam_vect[img->lst->id](img, img->lst->obj);
		img->lst = img->lst->next;
	}
}
void	light_on(t_img *img)
{
	img->light = img->l_start;
	while (img->light)
	{
		img->light->on = ON;
		img->light = img->light->next;
	}
}
void	draw_img(t_img *img)
{
	int		x;
	int		y;

	screen_center(img);
	object_to_cam(img);
	img->ray_start = img->cam->pos;
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			img->u_view = camera(img, x, y);
			ft_bzero(&img->node, sizeof(img->node));
			img->node.dist = -1;
			// if (x == 255 && y == 255)
			node_judge(img);
			if (img->node.dist != -1)
			{
				shadow(img);
				// if (x == 254 && y == 254)
				// if (img->light->on == OFF)
				pixel_put(img, x, y, color(img));
				// else
				// pixel_put(img, x, y, (255 << 16) + (255 << 8) + 255);
			}
			else
				pixel_put(img, x, y, 0);
			light_on(img);
			x++;
		}
		y++;
	}
}

void	calc(t_img *img)
{
	// if (!img->lst)
	// {
	// 	// sp_init(img, vect_init(3, 0, 25), 1, rgb_init(255, 0, 0));
	// 	// sp_init(img, vect_init(2, 0, 20), 1, rgb_init(0, 255, 0));
	// 	// sp_init(img, vect_init(1, 0, 15), 1, rgb_init(0, 0, 255));
	// 	// sp_init(img, vect_init(0, 0, 10), 1, rgb_init(255, 255, 255));
	// 	// sp_init(img, vect_init(-1, 0, 5), 1, rgb_init(255, 0, 0));
	// 	sp_init(img, vect_init(0, 0, 5), 1, rgb_init(255, 0, 0));
	// 	// printf("aaa\n");
	// 	light_init(img, vect_init(-5, 5, -5));
	// 	// light_init(img, vect_init(150, 150, -150));
	// 	// img->cam = vect_init(0, 0, -30);
	// 	img->o_start = img->lst;
	// }
	while (img->cam)
	{
		draw_img(img);
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
	func_ary_init(img);
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
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(sp, SP)))
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
