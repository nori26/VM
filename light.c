/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/21 23:12:15 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int	light(t_vect point, t_vect sp, t_vect u_view)
{
	int		ret;
	double	cos_nl;
	t_vect	u_normal;
	t_vect	p_light;
	t_vect	u_light;

	ret = (int)(255 * AMB);
	p_light = vect_init(-5, 5, -5);
	u_normal = vect_unit(vect_sub(point, sp));
	u_light = vect_unit(vect_sub(p_light, point));
	cos_nl = dot(u_light, u_normal);
	if (cos_nl > 0)
		ret += spec(u_view, u_light, u_normal, cos_nl);
	return (ret += (cos_nl > 0) * (int)(cos_nl * 255 * DIFF));
}

int spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * cos_nl), u_light));
	cos_vr = dot(u_view, u_ref);
	return (255 * SPEC * pow(cos_vr, GLOSS));
	// return (cos_vr > 0 ? 255 * SPEC * pow(cos_vr, GLOSS) : 0);
}