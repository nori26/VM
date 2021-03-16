/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 07:02:53 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 08:01:00 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double	shadow_node_dist(t_pic *img, t_vect u_ray)
{
	void	*obj;
	int		id;
	t_vect	to_raystart;

	id = img->lst->id;
	obj = img->lst->obj;
	to_raystart = img->f_ret_to_raystart[id](obj, img->ray_start);
	return (img->f_node_judge[id](img, obj, u_ray, to_raystart));
}

void	shadow(t_pic *img)
{
	double dist;
	double dist_from_light;
	t_vect u_ray;

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
