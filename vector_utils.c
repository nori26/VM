/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:28:53 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:07:22 by nosuzuki         ###   ########.fr       */
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
