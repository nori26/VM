/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_update_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 06:53:50 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:54:12 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
