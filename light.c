/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/07 20:39:44 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double	light(t_img *img)
{
	double	ret;
	double	nl_dot;
	t_vect	u_light;

	ret = 0;
	ret = AMB; //amb
	u_light = vect_unit(vect_sub(img->light->pos, img->node.pos));
	nl_dot = dot(u_light, img->node.normal);
	if (nl_dot > 0)
	{
		ret += nl_dot * img->light->pow * DIFF;
		ret += spec(img->u_view, u_light, img->node.normal, nl_dot);
	}
	return (ret > 1 ? 1 : ret);
}

double spec(t_vect u_view, t_vect u_light, t_vect u_normal, double nl_dot)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * nl_dot), u_light));
	cos_vr = dot(vect_mult(u_view, -1), u_ref);
	return (cos_vr > 0 ? SPEC * pow(cos_vr, GLOSS) : 0);
}

int		color(t_rgb obj, t_llist light, double ref)
{
	int r;
	int g;
	int b;

	r = 255 * obj.r * light.rgb.r * ref;
	g = 255 * obj.g * light.rgb.g * ref;
	b = 255 * obj.b * light.rgb.b * ref;
	return ((r << 16) + (g << 8) + b);
}
