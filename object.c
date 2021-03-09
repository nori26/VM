/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/09 10:27:08 by nosuzuki         ###   ########.fr       */
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

t_clist	*ft_lstnew_c(t_clist c)
{
	t_clist *cam;

	if (!(cam = malloc(sizeof(t_clist))))
		return (NULL);
	*cam = c;
	cam->next = NULL;
	return (cam);
}

t_llist		*ft_lstnew_l(t_llist l)
{
	t_llist *light;

	if (!(light = malloc(sizeof(t_llist))))
		return (NULL);
	*light = l;
	light->next = NULL;
	return (light);
}

double		sphere(t_img *img, t_sp *sp)
{
	double b;
	double c;
	double dist;

	b = 2 * dot(img->u_view, sp->to_cam);
	c = pow(vect_len(sp->to_cam), 2) - sp->r * sp->r;
	if (!(dist = quadratic_formula(1, b, c)))
		return (-1);
	return (dist);
}

double		dist_to_plane(double *vndot, t_vect u_view, t_vect to_cam, t_vect n)
{
	double dist;

	if (!(*vndot = dot(vect_mult(u_view, -1), n)))
		return (-1);
	if ((dist = dot(to_cam, n) / *vndot) <= 0)
		return (-1);
	return (dist);
}

double		plane(t_img *img, t_pl *pl)
{
	double dist;
	double vn_dot;

	if ((dist = dist_to_plane(&vn_dot, img->u_view, pl->to_cam, pl->n)) == -1)
		return (-1);
	pl->n = vn_dot > 0 ? pl->n : vect_mult(pl->n, -1);
	return (dist);
}

double			square(t_img *img, t_sq *sq)
{
	t_vect node;
	t_vect o_p;
	double dist;
	double vn_dot;

	if ((dist = dist_to_plane(&vn_dot, img->u_view, sq->to_cam, sq->n)) == -1)
		return (-1);
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
		return (-1);
	sq->n = vn_dot > 0 ? sq->n : vect_mult(sq->n, -1);
	return (dist);
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
		return (-1);
	return (0);
}

double			triangle(t_img *img, t_tr *tr)
{
	double dist;
	double vn_dot;
	t_vect node;

	if ((dist = dist_to_plane(&vn_dot, img->u_view, tr->to_cam, tr->n)) == -1)
		return (-1);
	img->v_view = vect_mult(img->u_view, dist);
	node = vect_add(img->v_view, img->cam->pos);
	if (is_inside(*tr, node))
		return (-1);
	tr->n = vn_dot > 0 ? tr->n : vect_mult(tr->n, -1);
	return (dist);
}
