/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/08 14:08:38 by nosuzuki         ###   ########.fr       */
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
	printf("%.20f\n", vect_len(img->node.normal));
	if (nl_dot > 0)
	{
		ret += nl_dot /* DIFF*/;
		ret += spec(img->u_view, u_light, img->node.normal, nl_dot);
		ret *= img->light->pow;
	}
	return (ret);
}

double spec(t_vect u_view, t_vect u_light, t_vect u_normal, double nl_dot)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * nl_dot), u_light));
	cos_vr = dot(vect_mult(u_view, -1), u_ref);
	return (cos_vr < 0 ? 0 : /*SPEC * */pow(cos_vr, GLOSS));
}

int		color(t_img *img)
{
	double	r;
	double	g;
	double	b;
	double	ref;

	r = img->amb->rgb.r * img->amb->pow;
	g = img->amb->rgb.g * img->amb->pow;
	b = img->amb->rgb.b * img->amb->pow;
	img->light = img->l_start;
	while (img->light)
	{
		ref = light(img);
		r += img->light->rgb.r * ref;
		g += img->light->rgb.g * ref;
		b += img->light->rgb.b * ref;
		img->light = img->light->next;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
	}
	r = img->node.rgb.r + r;
	g = img->node.rgb.g + g;
	b = img->node.rgb.b + b;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((((int)r << 16) + ((int)g << 8) + (int)b));
}

