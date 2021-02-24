/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:28:53 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/24 20:58:04 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_vect			vect_init(double x, double y, double z)
{
	t_vect ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
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

double			dot(t_vect v1, t_vect v2)
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

// t_vect			point_to_vect(double x, double y, t_img img)
// {
// 	t_vect ret;

// 	ret.x = 2 * x / (img.w - 1) - 1;
// 	ret.y = -2 * y / (img.h - 1) + 1;
// 	ret.z = 0;
// 	return (ret);
// }

t_vect			vect_unit(t_vect v)
{
	double len;

	len = vect_len(v);
	return (vect_init(v.x / len, v.y / len, v.z / len));
}

double			vect_len(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
