/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 06:52:10 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:52:52 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
