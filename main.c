/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:55:51 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/13 21:02:45 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "puts.h"

void	vect_init_unit_view(t_pic *img, int x, int y)
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
}

void	vect_init_cam_to_screen_center(t_pic *img)
{
	double distance;

	distance = img->w / (2 * tan(img->cam->fov / 2));
	img->cam->cent = vect_mult(img->cam->n, distance);
}

double	shadow_node_dist(t_pic *img, t_vect u_ray)
{
	void	*obj;
	int		id;
	t_vect	to_raystart;

	id = img->lst->id;
	obj = img->lst->obj;
	to_raystart = img->f_ret_to_raystart[id](obj, img->ray_start);
	return(img->f_node_judge[id](img, obj, u_ray, to_raystart));
}

void	shadow(t_pic *img)
{
	double 	dist;
	double 	dist_from_light;
	t_vect 	u_ray;

	img->shad = 1;
	img->light = img->l_start;
	while (img->light)
	{
		u_ray = vect_unit(vect_sub(img->light->pos, img->node.pos));
		img->ray_start = vect_add(img->node.pos, vect_mult(u_ray, EPSILON));
		dist_from_light = vect_len(vect_sub(img->light->pos, img->ray_start));
		img->lst = img->o_start;
		while ((img->lst))
		{
			dist = shadow_node_dist(img, u_ray);
			if (dist != -1 && dist_from_light - dist > EPSILON)
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

void	node_judge(t_pic *img)
{
	int		id;
	void	*obj;
	double	dist;
	t_vect	to_cam;

	ft_bzero(&img->node, sizeof(img->node));
	img->node.dist = -1;
	img->ray_start = img->cam->pos;
	img->lst = img->o_start;
	while ((img->lst))
	{
		id = img->lst->id;
		obj = img->lst->obj;
		to_cam = img->f_ret_to_cam[id](obj);
		dist = img->f_node_judge[id](img, obj, img->u_view,	to_cam);
		if (dist != -1 && (img->node.dist == -1 || (dist < img->node.dist)))
			img->f_update_node[img->lst->id](img, dist, img->lst->obj);
		img->lst = img->lst->next;
	}
}

void	vect_init_object_to_cam(t_pic *img)
{
	img->lst = img->o_start;
	while (img->lst)
	{
		img->f_to_cam_vect[img->lst->id](img, img->lst->obj);
		img->lst = img->lst->next;
	}
}
void	light_on(t_pic *img)
{
	img->light = img->l_start;
	while (img->light)
	{
		img->light->on = ON;
		img->light = img->light->next;
	}
}
void	draw_img(t_pic *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			vect_init_unit_view(img, x, y);
			node_judge(img);
			if (img->node.dist != -1)
			{
				shadow(img);
				pixel_put(img, x, y, color(img));
			}
			else
				pixel_put(img, x, y, 0);
			light_on(img);
			x++;
		}
		y++;
	}
}

void	calc(t_pic *img)
{
	while (1)
	{
		img->cam->img = mlx_new_image(img->mlx, img->w, img->h);
		img->cam->addr = mlx_get_data_addr(img->cam->img, &img->bpp,
						&img->line_length, &img->endian);
		vect_init_object_to_cam(img);
		vect_init_cam_to_screen_center(img);
		draw_img(img);
		img->cam = img->cam->next;
		if (img->cam == img->c_start)
			break ;
	}
	img->cam = img->c_start;
}

int		main_loop(t_pic *img)
{
	mlx_put_image_to_window(img->mlx, img->win, img->cam->img, 0, 0);
	return (0);
}

void	make_img(t_pic *img)
{
	int w = 0;
	int h = 0;

    img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, img->w, img->h, "miniRT");
	mlx_get_screen_size(img->mlx, &w, &h);
	img->w = img->w > w ? w : img->w;
	img->h = img->h > h ? h : img->h;
	func_ary_init(img);
	calc(img);
	mlx_hook(img->win, 2, 1, close2, img);
	mlx_hook(img->win, 33, 1 << 17, close1, img);
	mlx_loop_hook(img->mlx, &main_loop, img);
    mlx_loop(img->mlx);
}

int     main(int argc, char *argv[])
{
	t_pic 	img;

	if (argc != 2 && argc != 3)
		return (0);
	ft_bzero(&img, sizeof(img));
	if (argc > 2 && !(img.bmp += !ft_strncmp(argv[2], "--save", 7)))
		return 0;
	read_rt(&img, argv[1]);
	make_img(&img);
}

// t_rgb	rgb_init(int r, int g, int b)
// {
// 	t_rgb color;

// 	color.r = r / 255.0;
// 	color.g = g / 255.0;
// 	color.b = b / 255.0;
// 	return (color);
// }

// int	sp_init(t_img *img, t_vect o, double r, t_rgb rgb)
// {
// 	t_sp	*sp;

// 	if (!(sp = malloc(sizeof(t_sp))))
// 		return (-1);
// 	sp->o = o;
// 	sp->r = r;
// 	sp->rgb = rgb;
// 	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(sp, SP)))
// 		return (-1);
// 	return (0);
// }

// void light_init(t_img *img, t_vect l)
// {
// 	t_llist light;

// 	light.pos = l;
// 	light.rgb = rgb_init(255, 255, 255);
// 	light.pow = 1;
// 	img->light = ft_lstnew_l(light);
// }
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