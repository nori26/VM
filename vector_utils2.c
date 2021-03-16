/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 05:53:12 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 08:03:24 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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

t_vect			vect_unit(t_vect v)
{
	double len;

	len = vect_len(v);
	return (vect_init(v.x / len, v.y / len, v.z / len));
}

double			vect_len(t_vect v)
{
	return (sqrt(dot(v, v)));
}

int				check_parallel(t_vect a, t_vect b, t_vect c)
{
	t_vect v1;
	t_vect v2;

	v1 = vect_sub(a, b);
	v2 = vect_sub(a, c);
	return (!vect_len(cross(v1, v2)));
}
