/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 07:01:12 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 07:01:53 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	vect_init_object_to_cam(t_pic *img)
{
	img->lst = img->o_start;
	while (img->lst)
	{
		img->f_to_cam_vect[img->lst->id](img, img->lst->obj);
		img->lst = img->lst->next;
	}
}

void	vect_init_cam_to_screen_center(t_pic *img)
{
	double distance;

	distance = img->w / (2 * tan(img->cam->fov / 2));
	img->cam->cent = vect_mult(img->cam->n, distance);
}
