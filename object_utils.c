/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:22:29 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/14 07:44:15 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void		vprint(t_vect v)
{
	printf("x : % .30f\ny : % .30f\nz : % .30f\n", v.x, v.y, v.z);
}

void		func_ary_init(t_pic *img)
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
	img->f_ret_to_raystart[SP] = ret_to_raystart_sp;
	img->f_ret_to_raystart[PL] = ret_to_raystart_pl;
	img->f_ret_to_raystart[SQ] = ret_to_raystart_sq;
	img->f_ret_to_raystart[CY] = ret_to_raystart_cy;
	img->f_ret_to_raystart[TR] = ret_to_raystart_tr;
}

t_vect		ret_to_raystart_sp(t_sp *sp, t_vect ray_start)
{
	return (vect_sub(ray_start, sp->o));
}

t_vect		ret_to_raystart_pl(t_pl *pl, t_vect ray_start)
{
	return (vect_sub(ray_start, pl->p));
}

t_vect		ret_to_raystart_sq(t_sq *sq, t_vect ray_start)
{
	return (vect_sub(ray_start, sq->p));
}

t_vect		ret_to_raystart_cy(t_cy *cy, t_vect ray_start)
{
	return (vect_sub(ray_start, cy->p));
}

t_vect		ret_to_raystart_tr(t_tr *tr, t_vect ray_start)
{
	return (vect_sub(ray_start, tr->a));
}

t_vect		ret_to_cam_sp(t_sp *sp)
{
	return (sp->to_cam);
}

t_vect		ret_to_cam_pl(t_pl *pl)
{
	return (pl->to_cam);
}

t_vect		ret_to_cam_sq(t_sq *sq)
{
	return (sq->to_cam);
}

t_vect		ret_to_cam_cy(t_cy *cy)
{
	return (cy->to_cam);
}

t_vect		ret_to_cam_tr(t_tr *tr)
{
	return (tr->to_cam);
}

void		to_cam_vect_sp(t_pic *img, t_sp *sp)
{
	sp->to_cam = vect_sub(img->cam->pos, sp->o);
}

void		to_cam_vect_pl(t_pic *img, t_pl *pl)
{
	pl->to_cam = vect_sub(img->cam->pos, pl->p);
}

void		to_cam_vect_sq(t_pic *img, t_sq *sq)
{
	sq->to_cam = vect_sub(img->cam->pos, sq->p);
}

void		to_cam_vect_cy(t_pic *img, t_cy *cy)
{
	cy->to_cam = vect_sub(img->cam->pos, cy->p);
}

void		to_cam_vect_tr(t_pic *img, t_tr *tr)
{
	tr->to_cam = vect_sub(img->cam->pos, tr->a);
}

void		update_node_sp(t_pic *img, double dist, t_sp *sp)
{
	t_vect norm;

	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	norm = vect_unit(vect_sub(img->node.pos, sp->o));
	sp->n = vect_len(sp->to_cam) > sp->r ? norm : vect_mult(norm, -1);
	update_node(img, dist, sp->rgb, sp->n);
}

void		update_node_pl(t_pic *img, double dist, t_pl *pl)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, pl->rgb, pl->n);
}

void		update_node_sq(t_pic *img, double dist, t_sq *sq)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, sq->rgb, sq->n);
}

void		update_node_cy(t_pic *img, double dist, t_cy *cy)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, cy->rgb, cy->node_n);
}

void		update_node_tr(t_pic *img, double dist, t_tr *tr)
{
	img->v_view = vect_mult(img->u_view, dist);
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	update_node(img, dist, tr->rgb, tr->n);
}

void		update_node(t_pic *img, double dist, t_rgb rgb, t_vect n)
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

// double		quadratic_formula(double a, double b, double c)
// {
// 	double d;
// 	double small;
// 	double large;
// 	double root_d;

// 	if (!a || (d = b * b - 4 * a * c) < 0)
// 		return (-1);
// 	root_d = sqrt(d);
// 	small = (-b - root_d) / (2 * a);
// 	if (small > 0)
// 		return (small);
// 	large = (-b + root_d) / (2 * a);
// 	if (large > 0)
// 		return (large);
// 	return (-1);
// }

double		quadratic_formula(double a, double b, double c, double *ans)
{
	double d;
	double root_d;

	if (!a || (d = b * b - 4 * a * c) < 0)
		return (-1);
	root_d = sqrt(d);
	ans[0] = (-b - root_d) / (2 * a);
	ans[1] = (-b + root_d) / (2 * a);
	if (ans[1] <= 0)
		return (-1);
	return (0);
}

double		quadratic_formularge(double a, double b, double c)
{
	double d;
	double ans;
	double root_d;

	if (!a || (d = b * b - 4 * a * c) < 0)
		return (-1);
	root_d = sqrt(d);
	if ((ans = (-b + root_d) / (2 * a)) > 0)
		return (ans);
	return (-1);
}


int			is_inside(t_tr tr, t_vect node)
{
	int8_t	result_ab;
	int8_t	result_bc;
	int8_t	result_ca;

	tr.ap = vect_sub(node, tr.a);
	tr.bp = vect_sub(node, tr.b);
	tr.cp = vect_sub(node, tr.c);
	if (!vect_len(tr.cross_a = cross(tr.ap, tr.ab)) ||
		!vect_len(tr.cross_b = cross(tr.bp, tr.bc)) ||
		!vect_len(tr.cross_c = cross(tr.cp, tr.ca)))
		return (-1);
	tr.cross_a = vect_unit(cross(tr.ap, tr.ab));
	tr.cross_b = vect_unit(cross(tr.bp, tr.bc));
	tr.cross_c = vect_unit(cross(tr.cp, tr.ca));
	result_ab = dot(tr.cross_a, tr.cross_b) > 0;
	result_bc = dot(tr.cross_b, tr.cross_c) > 0;
	result_ca = dot(tr.cross_c, tr.cross_a) > 0;
	// printf("result_ab % d\nresult_bc % d\nresult_ca % d\n", result_ab, result_bc, result_ca);
	// printf("dot_ab    % f\ndot_bc    % f\ndot_ca    % f\n", dot(tr.cross_a, tr.cross_b), dot(tr.cross_b, tr.cross_c), dot(tr.cross_c, tr.cross_a));
	// printf("cross_a.x % f\ncross_a.y % f\ncross_a.z % f\n", tr.cross_a.x, tr.cross_a.y, tr.cross_a.z);
	// printf("cross_b.x % f\ncross_b.y % f\ncross_b.z % f\n", tr.cross_b.x, tr.cross_b.y, tr.cross_b.z);
	// printf("cross_c.x % f\ncross_c.y % f\ncross_c.z % f\n\n", tr.cross_c.x, tr.cross_c.y, tr.cross_c.z);
	// printf("tr.bp.x   % f\ntr.bp.y   % f\ntr.bp.z   % f\n\n", tr.bp.x, tr.bp.y, tr.bp.z);
	// printf("tr.bc.x   % f\ntr.bc.y   % f\ntr.bc.z   % f\n\n", tr.bc.x, tr.bc.y, tr.bc.z);
	// printf("cross.x   % f\ncross.y   % f\ncross.z   % f\n\n", cross(tr.bp, tr.bc).x, cross(tr.bp, tr.bc).y, cross(tr.bp, tr.bc).z);
	return ((result_ab + result_bc + result_ca) % 3);
}
