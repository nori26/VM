/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/08 23:01:42 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_idlst	*ft_lstnew_id(void *obj, int id)
{
	t_idlst *lst;

	if (!(lst = malloc(sizeof(t_idlst))))
		return (NULL);
	lst->id = id;
	lst->obj = obj;
	lst->next = NULL;
	return (lst);
}

t_idlst	*ft_lstadd_front_o(t_idlst **lst, t_idlst *new)
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

t_idlst	*ft_lstnew_o(void *obj, void *func)
{
	t_idlst *lst;

	if (!(lst = malloc(sizeof(t_idlst))))
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
	*cam = c;
	cam->next = NULL;
	return (cam);
}

t_llist	*ft_lstnew_l(t_llist l)
{
	t_llist *light;

	if (!(light = malloc(sizeof(t_llist))))
		return (NULL);
	*light = l;
	light->next = NULL;
	return (light);
}

double			sphere(t_img *img, t_sp *sp)
{
	double b;
	double c;
	double dist;
	t_vect o_cam;
	t_vect norm;

	o_cam = vect_sub(img->cam->pos, sp->o);
	b = 2 * dot(img->u_view, o_cam);
	c = pow(vect_len(o_cam), 2) - sp->r * sp->r;
	if (!(dist = quadratic_formula(1, b, c)))
		return (0);
	if (!(update_node(img, dist, sp->rgb)))
		return (0);
	norm = vect_unit(vect_sub(img->node.pos, sp->o));
	img->node.normal = vect_len(o_cam) > sp->r ? norm : vect_mult(norm, -1);
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
	img->node.normal = -vn_dot > 0 ? pl->n : vect_mult(pl->n, -1);
	return (0);
}

double			square(t_img *img, t_sq *sq)
{
	t_vect node;
	t_vect o_p;
	double dist;
	double vn_dot;

	if (!(vn_dot = dot(img->u_view, sq->n)))
		return (0);
	if ((dist = dot(vect_sub(sq->p, img->cam->pos), sq->n) / vn_dot) <= 0)
		return (0);
	img->v_view = vect_mult(img->u_view, dist);
	node = vect_add(img->v_view, img->cam->pos);
	o_p = vect_sub(node, sq->p);
	if (!sq->n.x && !sq->n.z)
		sq->u_x = vect_init(1, 0, 0);
	else
		sq->u_x = vect_init(
						-sq->n.z / sqrt(sq->n.x * sq->n.x + sq->n.z * sq->n.z),
						0,
						sq->n.x / sqrt(sq->n.x * sq->n.x + sq->n.z * sq->n.z));
	sq->u_y = vect_unit(cross(sq->u_x, sq->n));
	if (fabs(dot(o_p, sq->u_x)) > sq->size / 2 ||
		fabs(dot(o_p, sq->u_y)) > sq->size / 2)
		return (0);
	update_node(img, dist, sq->rgb);
	img->node.normal = -vn_dot > 0 ? sq->n : vect_mult(sq->n, -1);
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
	return (0);
}

double			triangle(t_img *img, t_tr *tr)
{
	double dist;
	double vn_dot;
	t_vect node;

	if (!(vn_dot = dot(img->u_view, tr->n)) ||
		((dist = dot(vect_sub(tr->a, img->cam->pos), tr->n) / vn_dot) <= 0))
		return (0);
	img->v_view = vect_mult(img->u_view, dist);
	node = vect_add(img->v_view, img->cam->pos);
	if (is_inside(*tr, node))
		return (0);
	update_node(img, dist, tr->rgb);
	img->node.normal = -vn_dot > 0 ? tr->n : vect_mult(tr->n, -1);
	return (0);
}
