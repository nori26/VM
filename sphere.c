/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/07 10:19:53 by nosuzuki         ###   ########.fr       */
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

double			quadratic_formula(double a, double b, double c)
{
	double d;
	double small;
	double large;
	double root_d;

	if ((d = b * b - 4 * a * c) < 0)
		return (0);
	root_d = sqrt(d);
	small = (-b - root_d) / (2 * a);
	if (small > 0)
		return (small);
	large = (-b + root_d) / (2 * a);
	if (large > 0)
		return (large);
	return (0);
}

double			square(t_img *img, t_sq *sq)
{
	(void)img;
	(void)sq;
	return (0);
}

double			cylinder(t_img *img, t_cy *cy)
{
	t_vect vn_cross;
	t_vect tmp;
	double a;
	double b;
	double c;

	vn_cross = cross(img->u_view, cy->n);
	tmp = cross(vect_sub(img->cam->pos, cy->p), cy->n);
	a = pow(vect_len(vn_cross), 2);
	b = 2 * dot(vn_cross, tmp);
	c = pow(vect_len(tmp), 2) - pow(cy->r, 2);
	if (!(a = quadratic_formula(a, b, c)))
		return (0);
	if (img->node.dist >= 0 && (a >= img->node.dist))
		return (0);
	return (0);
}

int ii;
double			triangle(t_img *img, t_tr *tr)
{
	double dist;
	double vn_dot;
	int8_t dot_result_ab;
	int8_t dot_result_bc;
	int8_t dot_result_ca;
	t_vect node;

	if (!(vn_dot = dot(img->u_view, tr->n)))
		return (0);
	if ((dist = dot(vect_sub(tr->a, img->cam->pos), tr->n) / vn_dot) <= 0)
		return (0);
	img->v_view = vect_mult(img->u_view, dist);
	node = vect_add(img->v_view, img->cam->pos);
	tr->ap = vect_sub(node, tr->a);
	tr->bp = vect_sub(node, tr->b);
	tr->cp = vect_sub(node, tr->c);
	tr->cross_a = vect_unit(cross(tr->ap, tr->ab));
	tr->cross_b = vect_unit(cross(tr->bp, tr->bc));
	tr->cross_c = vect_unit(cross(tr->cp, tr->ca));
	dot_result_ab = dot(tr->cross_a, tr->cross_b) > 0;
	dot_result_bc = dot(tr->cross_b, tr->cross_c) > 0;
	dot_result_ca = dot(tr->cross_c, tr->cross_a) > 0;
	if (((dot_result_ab + dot_result_bc + dot_result_ca) % 3))
		return (0);
	update_node(img, dist, tr->rgb);
	img->node.normal = -vn_dot > 0 ? tr->n : vect_mult(tr->n, -1);
	return (0);
}

double			sphere(t_img *img, t_sp *sp)
{
	double b;
	double c;
	double dist;
	t_vect o_cam;

	o_cam = vect_sub(img->cam->pos, sp->o);
	b = 2 * dot(img->u_view, o_cam);
	c = pow(vect_len(o_cam), 2) - sp->r * sp->r;
	if (!(dist = quadratic_formula(1, b, c)))
		return (0);
	if (!(update_node(img, dist, sp->rgb)))
		return (0);
	img->node.normal = vect_unit(vect_sub(img->node.pos, sp->o));
	return (0);
}

double			plane(t_img *img, t_pl *pl)
{
	double dist;
	double vn_dot;

	if (!(vn_dot = dot(img->u_view, pl->n)))
		return (0);
	if ((dist = dot(vect_sub(pl->p, img->cam->pos), pl->n) / vn_dot) <= 0)
		return (0);
	if (!(update_node(img, dist, pl->rgb)))
		return (0);
	//fixed vn_dot -> -1 * vn_dot
	img->node.normal = -vn_dot > 0 ? pl->n : vect_mult(pl->n, -1);
	// img->node.normal = vn_dot > 0 ? vect_mult(pl->n, -1) : pl->n;
	// printf("dot : %f\n", vn_dot);
	// vprint(img->u_view);
	return (0);
}

int			update_node(t_img *img, double dist, t_rgb rgb)
{
	if (img->node.dist >= 0 && (dist >= img->node.dist))
		return (0);
	img->v_view = vect_mult(img->u_view, dist);
	img->node.rgb = rgb;
	img->node.dist = dist;
	img->node.pos = vect_add(img->v_view, img->cam->pos);
	return (1);
}

void	vprint(t_vect v)
{
	printf("x : %f\ny : %f\nz : %f\n", v.x, v.y, v.z);
}