/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 05:36:08 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/21 07:27:51 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"


int	diff_ref(t_vect point, t_vect sp, t_vect view)
{
	t_vect normal;
	t_vect light;
	t_vect incidence;
	double diff;
	double spec = 0;
	double ret;

	light = vect_init(-5, 5, -5);
	normal = vect_unit(vect_sub(point, sp));
	incidence = vect_unit(vect_sub(light, point));
	diff = inner(incidence, normal);
	// printf("%f\n", vect_sub(vect_mult(normal, 2 * diff), incidence).len);
	spec = pow(inner(vect_mult(view, -1 ),vect_unit(vect_sub(vect_mult(normal, 2 * diff), incidence))), GLOSS);
	ret = (diff >= 0) * (int)(diff * 255 * DIFF) + (spec >= 0) * (int)(255 * spec * SPEC) + (int)(255 * AMB);
	return (ret);
}

// int spec_ref()
// {

// }