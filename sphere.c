/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/24 04:14:56 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_list	*ft_lstnew(void *obj, void *func)
{
	t_list *lst;

	if (!(lst = malloc(sizeof(t_list))))
		return (NULL);
	lst->obj = obj;
	lst->f = func;
	lst->next = NULL;
	return (lst);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

double			quadratic_formula(double a, double b, double d)
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
double			sphere(t_vect cam, t_vect view, t_img *img, t_sp *sp)
{
	double b;
	double c;
	double d;
	double t;
	double pos_len;

	b = 2 * dot(view, vect_sub(cam, sp->o));
	c = pow(vect_sub(cam, sp->o).len, 2) - sp->r * sp->r;
	if ((d = b * b - 4 * c) < 0)
		return (0);
	t = quadratic_formula(1, b, d);
	if ((pos_len = vect_len(vect_mult(view, t))) >= img->point.pos_len)
		return (0);
	img->point.pos_len = pos_len;
	img->point.pos = vect_add(vect_mult(view, t), cam);
	img->point.normal = vect_unit(vect_sub(img->point.pos, sp->o));
	return (1);
}
