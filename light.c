/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/25 19:48:04 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double	light(t_img *img)
{
	double	ret;
	double	cos_nl;
	t_vect	u_light;

	ret = AMB;
	u_light = vect_unit(vect_sub(img->light.pos, img->node.pos));
	cos_nl = dot(u_light, img->node.normal);
	if (cos_nl > 0)
		ret += spec(img->view, u_light, img->node.normal, cos_nl);
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

int		color(t_rgb obj, t_light light, double ref)
{
	int r;
	int g;
	int b;

	r = 255 * obj.r * light.rgb.r * ref;
	g = 255 * obj.g * light.rgb.g * ref;
	b = 255 * obj.b * light.rgb.b * ref;
	return ((r << 16) + (g << 8) + b);
}
