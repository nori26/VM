/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/08 22:12:41 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double	light_diff(t_img *img)
{
	double	nl_dot;
	t_vect	u_light;

	u_light = vect_unit(vect_sub(img->light->pos, img->node.pos));
	nl_dot = dot(u_light, img->node.normal);
	return (nl_dot > 0 ? nl_dot : 0);
}

double light_spec(t_img *img)
{
	t_vect ref;
	double cos_vr;
	double	nl_dot;
	t_vect	u_light;

	u_light = vect_unit(vect_sub(img->light->pos, img->node.pos));
	if ((nl_dot = dot(u_light, img->node.normal)) <= 0)
		return (0);
	ref = vect_unit(vect_sub(vect_mult(img->node.normal, 2 * nl_dot), u_light));
	cos_vr = dot(vect_mult(img->u_view, -1), ref);
	return (cos_vr < 0 ? 0 : pow(cos_vr, GLOSS));
}

double		primary_colors(t_img *img, double diff, double spec, char rgb)
{
	double ret;

	if (rgb == 'r')
	{
		ret = img->node.rgb.r * img->amb->rgb.r * img->amb->pow;
		ret += diff * img->light->rgb.r * img->light->pow * img->node.rgb.r;
		ret = (spec * img->light->rgb.r * img->light->pow * SPEC + ret) * 255;
	}
	if (rgb == 'g')
	{
		ret = img->node.rgb.g * img->amb->rgb.g * img->amb->pow;
		ret += diff * img->light->rgb.g * img->light->pow * img->node.rgb.g;
		ret = (spec * img->light->rgb.g * img->light->pow * SPEC + ret) * 255;
	}
	if (rgb == 'b')
	{
		ret = img->node.rgb.b * img->amb->rgb.b * img->amb->pow;
		ret += diff * img->light->rgb.b * img->light->pow * img->node.rgb.b;
		ret = (spec * img->light->rgb.b * img->light->pow * SPEC + ret) * 255;
	}
	if (ret > 255)
		ret = 255;
	return (ret);
}

int		color(t_img *img)
{
	t_rgb	rgb;
	double	diff;
	double	spec;

	ft_bzero(&rgb, sizeof(rgb));
	img->light = img->l_start;
	while (img->light)
	{
		diff = light_diff(img);
		spec = light_spec(img);
		rgb.r += primary_colors(img, diff, spec, 'r');
		rgb.g += primary_colors(img, diff, spec, 'g');
		rgb.b += primary_colors(img, diff, spec, 'b');
		img->light = img->light->next;
	}
	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
	return ((((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b));
}
