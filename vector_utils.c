/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:28:53 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/18 18:13:59 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_vect			vect_add(t_vect v1, t_vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vect			vect_sub(t_vect v1, t_vect v2)
{
	t_vect ret;

	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	ret.x = v1.x - v2.x;
	return (ret);
}

t_vect			vect_mult(t_vect v, double d)
{
	v.x *= d;
	v.y *= d;
	v.z *= d;
	return (v);
}

double			inner(t_vect v1, t_vect v2)
{
	double ret;

	ret = v1.x * v2.x + v1.y + v2.y * v1.z * v2.z;
	return (ret);
}

t_vect			cross(t_vect v1, t_vect v2)
{
	t_vect ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vect			point_to_vec(t_data img, t_point p, int win_w, int win_h)
{
	t_vect ret;

	ret.x = 2 * win_w / (img.w - 1) - 1;
	ret.y = -2 * win_h / (img.h - 1) - 1;
	ret.z = 0;
	return (ret);
}

double			vect_len(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

int				sphere(t_vect cam, t_vect p, t_vect sp, int r)
{
	double t;
	t_vect d;
	double a;
	double b;
	double c;

	d = vect_sub(p, cam);
	d.len = sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
	a = d.len * d.len;
	b = 2 * (inner(d, cam) - inner(d, sp));
	c = vect_len(vect_sub(cam, p)) - r * r;
	if ((t = b * b - 4 * a * c) < 0)
		return (0);
	else if (!t)


	t = -2 * 
}