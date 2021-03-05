/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/05 17:56:38 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_olist	*ft_lstadd_front_o(t_olist **lst, t_olist *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_clist	*ft_lstadd_front_c(t_clist **lst, t_clist *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_llist	*ft_lstadd_front_l(t_llist **lst, t_llist *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_olist	*ft_lstnew_o(void *obj, void *func)
{
	t_olist *lst;

	if (!(lst = malloc(sizeof(t_olist))))
		return (NULL);
	lst->obj = obj;
	lst->f = func;
	lst->next = NULL;
	return (lst);
}

t_clist	*ft_lstnew_c(t_clist c)
{
	t_clist *cam;

	if (!(cam = malloc(sizeof(t_clist))))
		return (NULL);
	cam->pos = c.pos;
	cam->n = c.n;
	cam->fov = c.fov;
	cam->addr = c.addr;
	cam->next = NULL;
	return (cam);
}

t_llist	*ft_lstnew_l(t_llist l)
{
	t_llist *light;

	if (!(light = malloc(sizeof(t_llist))))
		return (NULL);
	light->pos = l.pos;
	light->rgb = l.rgb;
	light->pow = l.pow;
	light->next = NULL;
	return (light);
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

double			square(t_img *img, t_sq *sq)
{
	(void)img;
	(void)sq;
	return (0);
}

double			cylinder(t_img *img, t_cy *cy)
{
	(void)img;
	(void)cy;
	return (0);
}

double			triangle(t_img *img, t_tr *tr)
{
	(void)img;
	(void)tr;
	return (0);
}


double			sphere(t_img *img, t_sp *sp)
{
	double b;
	double c;
	double d;
	double pos_len;
	t_vect view_spatial;

	b = 2 * dot(img->view, vect_sub(img->cam->pos, sp->o));
	c = pow(vect_len(vect_sub(img->cam->pos, sp->o)), 2) - sp->r * sp->r;
	if ((d = b * b - 4 * c) < 0)
		return (0);
	pos_len = quadratic_formula(1, b, d);
	view_spatial = vect_mult(img->view, pos_len);
	if (img->node.pos_len >= 0 && (pos_len >= img->node.pos_len))
		return (0);
	img->node.rgb = sp->rgb;
	img->node.pos_len = pos_len;
	img->node.pos = vect_add(view_spatial, img->cam->pos);
	img->node.normal = vect_unit(vect_sub(img->node.pos, sp->o));
	return (1);
}

int ii;
double			plane(t_img *img, t_pl *pl)
{
	double vn_dot;
	double len;

	if (!(vn_dot = dot(img->view, pl->n)))
		return (0);
	// if (!img->view.x && !img->view.y && img->view.z == 1)
	// 	exit (!!printf("dot : %f\n", vn_dot));
	pl->n = vn_dot > 0 ? pl->n : vect_mult(pl->n, -1);
	// if ((len = dot(vect_sub(pl->p, img->view), pl->n) / vn_dot) <= 0)
	// 	// return (printf("len: %f\n", len));
	// 	return (0);
	if ((len = -1 * dot(vect_sub(img->cam->pos, pl->p), pl->n) / vn_dot) <= 0)
			return (0);
	// if ((len = dot(vect_sub(pl->p, img->cam->pos), pl->n) / vn_dot) <= 0)
	// 	return (0);
	if (img->node.pos_len >= 0 && (len >= img->node.pos_len))
		return (0);
	img->node.rgb = pl->rgb;
	img->node.pos_len = len;
	img->node.pos = vect_add(vect_mult(img->view, len), img->cam->pos);
	img->node.normal = pl->n;
	// img->node.normal = vn_dot > 0 ? vect_unit(pl->n) : vect_unit(vect_mult(pl->n, -1));
	img->node.normal = vn_dot > 0 ? vect_mult(pl->n, -1) : pl->n;


	// if (ii++ % 1000 == 1)
	// {
	// 	printf("x %f\ny %f\ny %f\nvn_dot %f\n", pl->n.x, pl->n.y, 	pl->n.z, vn_dot);
	// 	printf("vx %f\nvy %f\nvz %f\n", img->view.x, img->view.y, 	img->view.z);
	// }
	// if (vn_dot > 0)
	// {
	// 	printf("%fnode : %f\nnode : %f\nnode : f\n", img->node.normal.x, img->node.normal.y, img->node.normal.z);
	// 	printf("%fpl : %f\npl : %f\n", pl->n.x, pl->n.y, pl->n.z);
	// }
	return (0);
}

// double		plane()