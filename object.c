/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/13 18:12:48 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double		sphere(t_pic *img, t_sp *sp, t_vect u_view, t_vect to_raystart)
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

double		plane(t_pic *img, t_pl *pl, t_vect u_view, t_vect to_raystart)
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

double		square(t_pic *img, t_sq *sq, t_vect u_view, t_vect to_raystart)
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

double		triangle(t_pic *img, t_tr *tr, t_vect u_view, t_vect to_raystart)
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
