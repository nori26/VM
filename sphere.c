/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/02 00:48:03 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_lst	*ft_lstadd_front_rt(t_lst **lst, t_lst *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_lst	*ft_lstnew_rt(void *obj, void *func)
{
	t_lst *lst;

	if (!(lst = malloc(sizeof(t_lst))))
		return (NULL);
	lst->obj = obj;
	lst->f = func;
	lst->next = NULL;
	return (lst);
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
double			plane(t_img *img, t_sp *pl)
{
	return (0);
}

double			square(t_img *img, t_sp *sq)
{
	return (0);
}

double			sphere(t_img *img, t_sp *sp)
{
	double b;
	double c;
	double d;
	double pos_len;
	t_vect view_spatial;

	b = 2 * dot(img->view, vect_sub(img->cam, sp->o));
	c = pow(vect_len(vect_sub(img->cam, sp->o)), 2) - sp->r * sp->r;
	if ((d = b * b - 4 * c) < 0)
		return (0);
	pos_len = quadratic_formula(1, b, d);
	view_spatial = vect_mult(img->view, pos_len);
	if (img->node.pos_len >= 0 && (pos_len >= img->node.pos_len))
		return (0);
	img->node.rgb = sp->rgb;
	img->node.pos_len = pos_len;
	img->node.pos = vect_add(view_spatial, img->cam);
	img->node.normal = vect_unit(vect_sub(img->node.pos, sp->o));
	return (1);
}

// double		plane()