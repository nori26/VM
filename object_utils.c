/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:22:29 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:56:07 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
	return ((result_ab + result_bc + result_ca) % 3);
}
