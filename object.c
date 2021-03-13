/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:15:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/13 14:46:05 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

t_idlst		*ft_lstnew_id(void *obj, int id)
{
	t_idlst *lst;

	if (!(lst = malloc(sizeof(t_idlst))))
		return (NULL);
	lst->id = id;
	lst->obj = obj;
	lst->next = NULL;
	return (lst);
}

t_idlst		*ft_lstadd_front_o(t_idlst **lst, t_idlst *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_clist		*ft_lstadd_front_c(t_clist **lst, t_clist *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_llist		*ft_lstadd_front_l(t_llist **lst, t_llist *new)
{
	if (*lst && new)
		new->next = *lst;
	*lst = new;
	return (new);
}

t_clist		*ft_lstnew_c(t_clist c)
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

double		sphere(t_img *img, t_sp *sp, t_vect u_view, t_vect to_raystart)
{
	double b;
	double c;
	double ans[2];

	(void)img;
	b = 2 * dot(u_view, to_raystart);
	c = pow(vect_len(to_raystart), 2) - sp->r * sp->r;
	if ((quadratic_formula(1, b, c, ans)) == -1)
		return (-1);
	if (ans[0] > 0)
		return (ans[0]);
	if (ans[1] > 0)
		return (ans[1]);
	return (-1);
}

double		plane(t_img *img, t_pl *pl, t_vect u_view, t_vect to_raystart)
{
	double dist;
	double vn_dot;

	(void)img;
	if ((dist = dist_to_plane(&vn_dot, u_view, to_raystart, pl->n)) == -1)
		return (-1);
	if (!img->shad)
		pl->n = vn_dot > 0 ? pl->n : vect_mult(pl->n, -1);
	return (dist);
}

double		square(t_img *img, t_sq *sq, t_vect u_view, t_vect to_raystart)
{
	t_vect node;
	t_vect o_p;
	double dist;
	double vn_dot;

	if ((dist = dist_to_plane(&vn_dot, u_view, to_raystart, sq->n)) == -1)
		return (-1);
	img->v_view = vect_mult(u_view, dist);
	node = vect_add(img->v_view, img->ray_start);
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
	if (!img->shad)
		sq->n = vn_dot > 0 ? sq->n : vect_mult(sq->n, -1);
	return (dist);
}

double		cy_height(double dist, t_vect to_raystart, t_cy *cy, t_vect u_view)
{
	t_vect v_view;
	double height;

	v_view = vect_mult(u_view, dist);
	height = dot(vect_add(v_view, to_raystart), cy->n);
	return (height);
}

t_vect		cy_normal(t_img *img, t_cy *cy, double dist, double height)
{
	t_vect node;
	t_vect normal;
	t_vect node_n;

	img->v_view = vect_mult(img->u_view, dist);
	node = vect_add(img->v_view, img->ray_start);
	normal = vect_add(cy->p, vect_mult(cy->n, height));
	node_n = vect_sub(node, normal);
	return (node_n);
}

double		cylinder(t_img *img, t_cy *cy, t_vect u_view, t_vect to_raystart)
{
	double dist;
	double height;
	double flag;
	double ans[2];
	t_vect tmp;
	t_vect vn_cross;

	flag = 1;
	vn_cross = cross(u_view, cy->n);
	tmp = cross(to_raystart, cy->n);
	if ((quadratic_formula(dot(vn_cross, vn_cross), 2 * dot(vn_cross, tmp),
		pow(vect_len(tmp), 2) - pow(cy->r, 2), ans)) == -1)
		return (-1);
	dist = ans[0];
	height = cy_height(dist, to_raystart, cy, u_view);
	if (height < 0 || height > cy->h || dist < 0)
	{
		dist = ans[1];
		height = cy_height(dist, to_raystart, cy, u_view);
		if (height < 0 || height > cy->h)
			return (-1);
		flag = -1;
	}
	if (!img->shad)
		cy->node_n = vect_mult(cy_normal(img, cy, dist, height), flag);
	return (dist);
}

double		triangle(t_img *img, t_tr *tr, t_vect u_view, t_vect to_raystart)
{
	double dist;
	double vn_dot;
	t_vect node;

	if ((dist = dist_to_plane(&vn_dot, u_view, to_raystart, tr->n)) == -1)
		return (-1);
	img->v_view = vect_mult(u_view, dist);
	node = vect_add(img->v_view, img->ray_start);
	if (is_inside(*tr, node))
		return (-1);
	if (!img->shad)
		tr->n = vn_dot > 0 ? tr->n : vect_mult(tr->n, -1);
	return (dist);
}
