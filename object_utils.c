/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:22:29 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/09 09:12:38 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void			vprint(t_vect v)
{
	printf("x : % .30f\ny : % .30f\nz : % .30f\n", v.x, v.y, v.z);
}

void			func_ary_init(t_img *img)
{
	img->f_crossing_judge[SP] = sphere;
	img->f_crossing_judge[PL] = plane;
	img->f_crossing_judge[SQ] = square;
	img->f_crossing_judge[CY] = cylinder;
	img->f_crossing_judge[TR] = triangle;
	img->f_update_node[SP] = update_node_sp;
	img->f_update_node[PL] = update_node_pl;
	img->f_update_node[SQ] = update_node_sq;
	img->f_update_node[CY] = update_node_cy;
	img->f_update_node[TR] = update_node_tr;
}

void			update_node_sp(t_img *img, double dist, t_sp *sp)
{
	t_vect norm;
	t_vect o_cam;

	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	norm = vect_unit(vect_sub(img->node.pos, sp->o));
	o_cam = vect_sub(img->cam->pos, sp->o);
	sp->n = vect_len(o_cam) > sp->r ? norm : vect_mult(norm, -1);
	update_node(img, dist, sp->rgb, sp->n);
}
void			update_node_pl(t_img *img, double dist, t_pl *pl)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, pl->rgb, pl->n);
}

void			update_node_sq(t_img *img, double dist, t_sq *sq)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, sq->rgb, sq->n);
}

void			update_node_cy(t_img *img, double dist, t_cy *cy)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, cy->rgb, cy->n);
}

void			update_node_tr(t_img *img, double dist, t_tr *tr)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, tr->rgb, tr->n);
}

void			update_node(t_img *img, double dist, t_rgb rgb, t_vect n)
{
	img->node.rgb = rgb;
	img->node.dist = dist;
	// img->node.pos = vect_add(img->v_view, img->cam->pos);
	img->node.normal = n;
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
