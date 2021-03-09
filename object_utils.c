/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:22:29 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/09 12:23:16 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void			vprint(t_vect v)
{
	printf("x : % .30f\ny : % .30f\nz : % .30f\n", v.x, v.y, v.z);
}

void			func_ary_init(t_img *img)
{
	img->f_node_judge[SP] = sphere;
	img->f_node_judge[PL] = plane;
	img->f_node_judge[SQ] = square;
	img->f_node_judge[CY] = cylinder;
	img->f_node_judge[TR] = triangle;
	img->f_update_node[SP] = update_node_sp;
	img->f_update_node[PL] = update_node_pl;
	img->f_update_node[SQ] = update_node_sq;
	img->f_update_node[CY] = update_node_cy;
	img->f_update_node[TR] = update_node_tr;
	img->f_to_cam_vect[SP] = to_cam_vect_sp;
	img->f_to_cam_vect[PL] = to_cam_vect_pl;
	img->f_to_cam_vect[SQ] = to_cam_vect_sq;
	img->f_to_cam_vect[CY] = to_cam_vect_cy;
	img->f_to_cam_vect[TR] = to_cam_vect_tr;
	img->f_ret_to_cam[SP] = ret_to_cam_sp;
	img->f_ret_to_cam[PL] = ret_to_cam_pl;
	img->f_ret_to_cam[SQ] = ret_to_cam_sq;
	img->f_ret_to_cam[CY] = ret_to_cam_cy;
	img->f_ret_to_cam[TR] = ret_to_cam_tr;
}

t_vect			ret_to_cam_sp(t_sp *sp)
{
	return (sp->to_cam);
}

t_vect			ret_to_cam_pl(t_pl *pl)
{
	return (pl->to_cam);
}

t_vect			ret_to_cam_sq(t_sq *sq)
{
	return (sq->to_cam);
}

t_vect			ret_to_cam_cy(t_cy *cy)
{
	return (cy->to_cam);
}

t_vect			ret_to_cam_tr(t_tr *tr)
{
	return (tr->to_cam);
}

void			to_cam_vect_sp(t_img *img, t_sp *sp)
{
	sp->to_cam = vect_sub(img->cam->pos, sp->o);
}

void			to_cam_vect_pl(t_img *img, t_pl *pl)
{
	pl->to_cam = vect_sub(img->cam->pos, pl->p);
}

void			to_cam_vect_sq(t_img *img, t_sq *sq)
{
	sq->to_cam = vect_sub(img->cam->pos, sq->p);
}

void			to_cam_vect_cy(t_img *img, t_cy *cy)
{
	cy->to_cam = vect_sub(img->cam->pos, cy->p);
}

void			to_cam_vect_tr(t_img *img, t_tr *tr)
{
	tr->to_cam = vect_sub(img->cam->pos, tr->a);
}

void			update_node_sp(t_img *img, double dist, t_sp *sp)
{
	t_vect norm;

	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	norm = vect_unit(vect_sub(img->node.pos, sp->o));
	sp->n = vect_len(sp->to_cam) > sp->r ? norm : vect_mult(norm, -1);
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
	img->node.normal = n;
}

double		dist_to_plane(double *vndot, t_vect u_view, t_vect to_cam, t_vect n)
{
	double dist;

	if (!(*vndot = dot(vect_mult(u_view, -1), n)))
		return (-1);
	if ((dist = dot(to_cam, n) / *vndot) <= 0)
		return (-1);
	return (dist);
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
