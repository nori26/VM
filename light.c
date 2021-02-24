/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/24 20:10:05 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int	light(t_img *img)
{
	int		ret;
	double	cos_nl;
	t_vect	u_light;

	ret = (int)(255 * AMB);
	u_light = vect_unit(vect_sub(img->light.pos, img->point.pos));
	cos_nl = dot(u_light, img->point.normal);
	if (cos_nl > 0)
		ret += spec(img->view, u_light, img->point.normal, cos_nl);
	return (ret += (cos_nl > 0) * (int)(cos_nl * 255 * DIFF));
}

int spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * cos_nl), u_light));
	cos_vr = dot(vect_mult(u_view, -1), u_ref);
	return (cos_vr > 0 ? 255 * SPEC * pow(cos_vr, GLOSS) : 0);
}