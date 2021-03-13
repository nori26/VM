/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/13 16:50:27 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double		sphere(t_img *img, t_sp *sp, t_vect u_view, t_vect to_raystart)
{
	double b;
	double c;
	double ans[2];

	(void)img;
	b = 2 * dot(u_view, to_raystart);
	c = pow(vect_len(to_raystart), 2) - sp->r * sp->r;
	if ((quadratic_formula(1, b, c, ans)) == -1)
		return (-1);
	if (ans[0] > 0)
		return (ans[0]);
	if (ans[1] > 0)
		return (ans[1]);
	return (-1);
}

double		plane(t_img *img, t_pl *pl, t_vect u_view, t_vect to_raystart)
{
	double dist;
	double vn_dot;

	(void)img;
	if ((dist = dist_to_plane(&vn_dot, u_view, to_raystart, pl->n)) == -1)
		return (-1);
	if (!img->shad)
		pl->n = vn_dot > 0 ? pl->n : vect_mult(pl->n, -1);
	return (dist);
}

double		square(t_img *img, t_sq *sq, t_vect u_view, t_vect to_raystart)
{
	t_vect node;
	t_vect o_p;
	double dist;
	double vn_dot;

	if ((dist = dist_to_plane(&vn_dot, u_view, to_raystart, sq->n)) == -1)
		return (-1);
	img->v_view = vect_mult(u_view, dist);
	node = vect_add(img->v_view, img->ray_start);
	o_p = vect_sub(node, sq->p);
	if (!sq->n.x && !sq->n.z)
		sq->u_x = vect_init(1, 0, 0);
	else
		sq->u_x = vect_init(
					-sq->n.z / sqrt(sq->n.x * sq->n.x + sq->n.z * sq->n.z),
					0,
					sq->n.x / sqrt(sq->n.x * sq->n.x + sq->n.z * sq->n.z));
	sq->u_y = vect_unit(cross(sq->u_x, sq->n));
	if (fabs(dot(o_p, sq->u_x)) > sq->size / 2 ||
		fabs(dot(o_p, sq->u_y)) > sq->size / 2)
		return (-1);
	if (!img->shad)
		sq->n = vn_dot > 0 ? sq->n : vect_mult(sq->n, -1);
	return (dist);
}

double		cy_height(double dist, t_vect to_raystart, t_cy *cy, t_vect u_view)
{
	t_vect v_view;
	double height;

	v_view = vect_mult(u_view, dist);
	height = dot(vect_add(v_view, to_raystart), cy->n);
	return (height);
}

t_vect		cy_normal(t_img *img, t_cy *cy, double dist, double height)
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

double		cylinder(t_img *img, t_cy *cy, t_vect u_view, t_vect to_raystart)
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

double		triangle(t_img *img, t_tr *tr, t_vect u_view, t_vect to_raystart)
{
	double dist;
	double vn_dot;
	t_vect node;

	if ((dist = dist_to_plane(&vn_dot, u_view, to_raystart, tr->n)) == -1)
		return (-1);
	img->v_view = vect_mult(u_view, dist);
	node = vect_add(img->v_view, img->ray_start);
	if (is_inside(*tr, node))
		return (-1);
	if (!img->shad)
		tr->n = vn_dot > 0 ? tr->n : vect_mult(tr->n, -1);
	return (dist);
}
