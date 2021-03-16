/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_ray_to_raystart.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 06:48:39 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:48:57 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
