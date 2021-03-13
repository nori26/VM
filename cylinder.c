/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 17:28:21 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/13 18:12:48 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double		cy_height(double dist, t_vect to_raystart, t_cy *cy, t_vect u_view)
{
	t_vect v_view;
	double height;

	v_view = vect_mult(u_view, dist);
	height = dot(vect_add(v_view, to_raystart), cy->n);
	return (height);
}

t_vect		cy_normal(t_pic *img, t_cy *cy, double dist, double height)
{
	t_vect node;
	t_vect center;

	img->v_view = vect_mult(img->u_view, dist);
	node = vect_add(img->v_view, img->ray_start);
	center = vect_add(cy->p, vect_mult(cy->n, height));
	return (vect_sub(node, center));
}

int			cy_dist(t_cy *cy, t_vect to_raystart, t_vect u_view, double *ans)
{
	double a;
	double b;
	double c;
	t_vect sn_cross;
	t_vect vn_cross;

	vn_cross = cross(u_view, cy->n);
	sn_cross = cross(to_raystart, cy->n);
	a = dot(vn_cross, vn_cross);
	b = 2 * dot(vn_cross, sn_cross);
	c = pow(vect_len(sn_cross), 2) - pow(cy->r, 2);
	if ((quadratic_formula(a, b, c, ans)) == -1)
		return (-1);
	return (0);
}

double		cylinder(t_pic *img, t_cy *cy, t_vect u_view, t_vect to_raystart)
{
	double dist;
	double height;
	double flag;
	double ans[2];

	flag = 1;
	if (cy_dist(cy, to_raystart, u_view, ans) == -1)
		return (-1);
	dist = ans[0];
	height = cy_height(dist, to_raystart, cy, u_view);
	if (height < 0 || height > cy->h || dist < 0)
	{
		flag = -1;
		dist = ans[1];
		height = cy_height(dist, to_raystart, cy, u_view);
		if (height < 0 || height > cy->h)
			return (-1);
	}
	if (!img->shad)
		cy->node_n = vect_mult(cy_normal(img, cy, dist, height), flag);
	return (dist);
}
