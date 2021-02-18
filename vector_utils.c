/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:28:53 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/18 19:45:57 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_vect			vect_init(double x, double y, double z)
{
	t_vect ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.len = sqrt(x * x + y * y + z * z);
	return (ret);
}

t_vect			vect_add(t_vect v1, t_vect v2)
{
	return (vect_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vect			vect_sub(t_vect v1, t_vect v2)
{
	return (vect_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vect			vect_mult(t_vect v, double d)
{
	return (vect_init(v.x * d, v.y * d, v.z * d));
}

double			inner(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y + v2.y * v1.z * v2.z);
}

t_vect			cross(t_vect v1, t_vect v2)
{
	return (vect_init(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
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
	a = d.len * d.len;
	b = 2 * (inner(d, cam) - inner(d, sp));
	c = vect_len(vect_sub(cam, p)) - r * r;
	if ((t = b * b - 4 * a * c) < 0)
		return (0);
	else if (!t)


	t = -2 * 
}