/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/23 23:58:56 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_list	*ft_lstnew(void *content)
{
	t_list *lst;

	if (!(lst = malloc(sizeof(t_list))))
		return (NULL);
	lst->obj = content;
	lst->f = content;
	lst->next = NULL;
	return (lst);
}

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
// double			sphere(t_vect cam, t_vect view, t_vect sp, double r)
// {
// 	double a;
// 	double b;
// 	double c;
// 	double d;

// 	a = 1;
// 	b = 2 * dot(view, vect_sub(cam, sp));
// 	c = pow(vect_sub(cam, sp).len, 2) - r * r;
// 	if ((d = b * b - 4 * a * c) < 0)
// 		return (0);
// 	return (quadratic_formula(a, b, c, d));
// }
double			sphere(t_vect cam, t_vect view, double r, void *obj)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_sp	*sp;

	sp = obj;
	a = 1;
	b = 2 * dot(view, vect_sub(cam, sp->o));
	c = pow(vect_sub(cam, sp->o).len, 2) - sp->r * sp->r;
	if ((d = b * b - 4 * a * c) < 0)
		return (0);
	return (quadratic_formula(a, b, c, d));
}
