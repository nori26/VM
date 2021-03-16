/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_ret_to_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 06:50:19 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:50:32 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
