/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:22:29 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/08 23:53:29 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void			vprint(t_vect v)
{
	printf("x : % .30f\ny : % .30f\nz : % .30f\n", v.x, v.y, v.z);
}

void			func_ary_init(t_img *img)
{
	img->f[SP] = sphere;
	img->f[PL] = plane;
	img->f[SQ] = square;
	img->f[CY] = cylinder;
	img->f[TR] = triangle;
}

int				update_node(t_img *img, double dist, t_rgb rgb)
{
	if (img->node.dist >= 0 && (dist >= img->node.dist))
		return (0);
	img->v_view = vect_mult(img->u_view, dist);
	img->node.rgb = rgb;
	img->node.dist = dist;
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	return (1);
}

double			quadratic_formula(double a, double b, double c)
{
	double d;
	double small;
	double large;
	double root_d;

	if ((d = b * b - 4 * a * c) < 0)
		return (0);
	root_d = sqrt(d);
	small = (-b - root_d) / (2 * a);
	if (small > 0)
		return (small);
	large = (-b + root_d) / (2 * a);
	if (large > 0)
		return (large);
	return (0);
}

double			quadratic_formularge(double a, double b, double c)
{
	double d;
	double ans;
	double root_d;

	if ((d = b * b - 4 * a * c) < 0)
		return (0);
	root_d = sqrt(d);
	ans = (-b + root_d) / (2 * a);
	if (ans > 0)
		return (ans);
	return (0);
}

int				is_inside(t_tr tr, t_vect node)
{
	int8_t	result_ab;
	int8_t	result_bc;
	int8_t	result_ca;

	tr.ap = vect_sub(node, tr.a);
	tr.bp = vect_sub(node, tr.b);
	tr.cp = vect_sub(node, tr.c);
	tr.cross_a = vect_unit(cross(tr.ap, tr.ab));
	tr.cross_b = vect_unit(cross(tr.bp, tr.bc));
	tr.cross_c = vect_unit(cross(tr.cp, tr.ca));
	result_ab = dot(tr.cross_a, tr.cross_b) > 0;
	result_bc = dot(tr.cross_b, tr.cross_c) > 0;
	result_ca = dot(tr.cross_c, tr.cross_a) > 0;
	return ((result_ab + result_bc + result_ca) % 3);
}
