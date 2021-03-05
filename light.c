/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/05 10:49:03 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int i;

double	light(t_img *img)
{
	double	ret;
	double	cos_nl;
	t_vect	u_light;

	ret = AMB; //amb
	u_light = vect_unit(vect_sub(img->light->pos, img->node.pos));
	cos_nl = dot(u_light, img->node.normal);
	if (cos_nl > 0)
	{
		if (i++ % 5 == 1)
		printf("bef %f\n", ret);
		if (i++ % 5 == 1)
			printf("u_l : %f\nn ; %f\ncos_nl : %f\n,")
		ret += spec(vect_unit(img->view), u_light, img->node.normal, cos_nl);
		if (i++ % 5 == 1)
		printf("aft %f\n", ret);

	}
	ret += (cos_nl > 0) * (cos_nl * img->light->pow);
	// if (i++ % 5 == 1)
	// 	printf("%f\n", ret);
	return (ret > 1 ? 1 : ret);
}

double spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl)
{
	t_vect u_ref;
	double cos_vr;

	u_ref = vect_unit(vect_sub(vect_mult(u_normal, 2 * cos_nl), u_light));
	cos_vr = dot(vect_mult(u_view, -1), u_ref);
	printf("cos_vr %f\n", cos_vr);
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
