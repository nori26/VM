/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/24 21:58:37 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double	light(t_img *img)
{
	double	ret;
	double	cos_nl;
	t_vect	u_light;

	ret = AMB;
	u_light = vect_unit(vect_sub(img->light.pos, img->point.pos));
	cos_nl = dot(u_light, img->point.normal);
	if (cos_nl > 0)
		ret += spec(img->view, u_light, img->point.normal, cos_nl);
	ret += (cos_nl > 0) * (cos_nl * DIFF);
	return (ret > 1 ? 1 : ret);
}

double spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * cos_nl), u_light));
	cos_vr = dot(vect_mult(u_view, -1), u_ref);
	return (cos_vr > 0 ? SPEC * pow(cos_vr, GLOSS) : 0);
}