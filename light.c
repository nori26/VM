/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/08 09:56:21 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double	light(t_img *img)
{
	double	ret;
	double	nl_dot;
	t_vect	u_light;

	ret = 0;
	u_light = vect_unit(vect_sub(img->light->pos, img->node.pos));
	nl_dot = dot(u_light, img->node.normal);
	if (nl_dot > 0)
	{
		ret += nl_dot /** DIFF*/;
		ret += spec(img->u_view, u_light, img->node.normal, nl_dot);
		ret *= img->light->pow;
	}
	return (ret > 1 ? 1 : ret);
}

double spec(t_vect u_view, t_vect u_light, t_vect u_normal, double nl_dot)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * nl_dot), u_light));
	cos_vr = dot(vect_mult(u_view, -1), u_ref);
	return (cos_vr > 0 ? /*SPEC * */pow(cos_vr, GLOSS) : 0);
}

int		color(t_img *img)
{
	double	r;
	double	g;
	double	b;
	double	ref;

	img->light = img->l_start;
	r = 0;
	g = 0;
	b = 0;
	while (img->light)
	{
		ref = light(img);
		r += img->light->rgb.r * ref;
		g += img->light->rgb.g * ref;
		b += img->light->rgb.b * ref;
		img->light = img->light->next;
	}
	r += img->amb->rgb.r * img->amb->pow;
	g += img->amb->rgb.g * img->amb->pow;
	b += img->amb->rgb.b * img->amb->pow;
	r = img->node.rgb.r * 255 * (r > 1 ? 1 : r);
	g = img->node.rgb.g * 255 * (g > 1 ? 1 : g);
	b = img->node.rgb.b * 255 * (b > 1 ? 1 : b);
	return ((((int)r << 16) + ((int)g << 8) + (int)b));
}
