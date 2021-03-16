/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 07:16:02 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 08:13:26 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
		dist = img->f_node_judge[id](img, obj, img->u_view, to_cam);
		if (dist != -1 && (img->node.dist == -1 || (dist < img->node.dist)))
			img->f_update_node[img->lst->id](img, dist, img->lst->obj);
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

void	make_img(t_pic *img)
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

void	ray_trace(t_pic *img)
{
	if (!img->cam)
		return ;
	while (1)
	{
		img->cam->img = mlx_new_image(img->mlx, img->w, img->h);
		img->cam->adr = mlx_get_data_addr(img->cam->img, &img->bpp,
						&img->width_bytes, &img->endian);
		vect_init_object_to_cam(img);
		vect_init_cam_to_screen_center(img);
		make_img(img);
		img->cam = img->cam->next;
		if (img->cam == img->c_start || img->bmp)
			break ;
	}
	img->cam = img->c_start;
}
