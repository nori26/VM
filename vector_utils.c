/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:28:53 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/19 23:43:09 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"
#include <math.h>


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
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vect			cross(t_vect v1, t_vect v2)
{
	return (vect_init(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}

t_vect			point_to_vect(double x, double y, t_win win)
{
	t_vect ret;

	ret.x = 2 * x / (win.w - 1) - 1;
	ret.y = -2 * y / (win.h - 1) + 1;
	ret.z = 0;
	return (ret);
}

t_vect			vect_unit(t_vect v)
{
	return (vect_init(v.x / v.len, v.y / v.len, v.z / v.len));
}

double			vect_len(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

int				sphere(t_vect cam, t_vect ray, t_vect sp, double r)
{
	double a;
	double b;
	double c;
	double d;

	a = 1;
	b = 2 * inner(ray, vect_sub(cam, sp));
	// printf("%f\n%f\n%f\n", ray.x, ray.y, ray.z);
	c = pow(vect_sub(cam, sp).len, 2) - r * r;
	if ((d = b * b - 4 * a * c) < 0 || (-b + sqrt(d)) / (2 * a) < 0)
		return (0);
	else
		return (1);
}