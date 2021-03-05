/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/22 00:16:07 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

double			quadratic_formula(double a, double b, double c, double d)
{
	double small;
	double large;
	double root_d;

	root_d = sqrt(d);
	small = (-b - root_d) / (2 * a);
	large = (-b + root_d) / (2 * a);
	return (small > 0 ? small : (large > 0) * large);
}
double			sphere(t_vect cam, t_vect view, t_vect sp, double r)
{
	double a;
	double b;
	double c;
	double d;

	a = 1;
	b = 2 * dot(view, vect_sub(cam, sp));
	c = pow(vect_sub(cam, sp).len, 2) - r * r;
	if ((d = b * b - 4 * a * c) < 0)
		return (0);
	return (quadratic_formula(a, b, c, d));
}