/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:32:37 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 19:42:15 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int	pl_init(char *data, t_pic *img)
{
	t_pl *pl;

	if (!ft_isspace(*data))
		return (PL);
	if (!(pl = malloc(sizeof(t_pl))))
		return (PL);
	if (split_comma(trim_space(&data), &pl->p.x, &pl->p.y, &pl->p.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&pl->n.x, &pl->n.y, &pl->n.z) < 0 ||
		(!pl->n.x && !pl->n.y && !pl->n.z))
		return (freeturn((char **)&pl, PL));
	pl->n = vect_unit(pl->n);
	if (parse_rgb(data, &pl->rgb.r, &pl->rgb.g, &pl->rgb.b) < 0)
		return (freeturn((char **)&pl, PL));
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(pl, PL)))
		return (freeturn((char **)&pl, PL));
	return (INT_MIN);
}
int	sp1_init(char *data, t_pic *img)
{
	t_sp	*sp;

	if (!ft_isspace(*data))
		return (SP);
	if (!(sp = malloc(sizeof(t_sp))))
		return (SP);
	if (split_comma(trim_space(&data),
		&sp->o.x, &sp->o.y, &sp->o.z) < 0)
		return (freeturn((char **)&sp, SP));
	if ((sp->r = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		sp->r == INFINITY)
		return (freeturn((char **)&sp, SP));
	printf("%g  ", sp->r);
	sp->r /= 2;
	if (parse_rgb(data, &sp->rgb.r, &sp->rgb.g, &sp->rgb.b) < 0)
		return (freeturn((char **)&sp, SP));
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(sp, SP)))
		return (freeturn((char **)&sp, SP));
	return (INT_MIN);
}

int	sq_init(char *data, t_pic *img)
{
	t_sq *sq;

	if (!ft_isspace(*data))
		return (SQ);
	if (!(sq = malloc(sizeof(t_sq))))
		return (SQ);
	if (split_comma(trim_space(&data), &sq->p.x, &sq->p.y, &sq->p.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&sq->n.x, &sq->n.y, &sq->n.z) < 0 || (!sq->n.x && !sq->n.y && !sq->n.z))
		return (freeturn((char **)&sq, SQ));
	sq->n = vect_unit(sq->n);
	if ((sq->size = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		sq->size == INFINITY)
		return (freeturn((char **)&sq, SQ));
	printf("%g  ", sq->size);
	if (parse_rgb(data, &sq->rgb.r, &sq->rgb.g, &sq->rgb.b) < 0)
		return (freeturn((char **)&sq, SQ));
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(sq, SQ)))
		return (freeturn((char **)&sq, SQ));
	return (INT_MIN);
}

int	cy_init(char *data, t_pic *img)
{
	t_cy *cy;

	if (!ft_isspace(*data))
		return (CY);
	if (!(cy = malloc(sizeof(t_cy))))
		return (CY);
	if (split_comma(trim_space(&data), &cy->p.x, &cy->p.y, &cy->p.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&cy->n.x, &cy->n.y, &cy->n.z) < 0 || (!cy->n.x && !cy->n.y && !cy->n.z))
		return (freeturn((char **)&cy, CY));
	cy->n = vect_unit(cy->n);
	if ((cy->r = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		cy->r == INFINITY)
		return (freeturn((char **)&cy, CY));
	printf("%g  ", cy->r);
	cy->r /= 2;
	if ((cy->h = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		cy->h == INFINITY)
		return (freeturn((char **)&cy, CY));
	printf("%g  ", cy->h);
	if (parse_rgb(data, &cy->rgb.r, &cy->rgb.g, &cy->rgb.b) < 0)
		return (freeturn((char **)&cy, CY));
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(cy, CY)))
		return (freeturn((char **)&cy, CY));
	return (INT_MIN);
}

int	tr_init(char *data, t_pic *img)
{
	t_tr *tr;

	if (!ft_isspace(*data) || !(tr = malloc(sizeof(t_tr))))
		return (TR);
	if (split_comma(trim_space(&data), &tr->a.x, &tr->a.y, &tr->a.z) < 0 ||
		split_comma(trim_space(&data), &tr->b.x, &tr->b.y, &tr->b.z) < 0 ||
		split_comma(trim_space(&data), &tr->c.x, &tr->c.y, &tr->c.z) < 0)
		return (freeturn((char **)&tr, TR));
	if (check_parallel(tr->a, tr->b, tr->c))
		return (freeturn((char **)&tr, TR));
	tr->ab = vect_sub(tr->b, tr->a);
	tr->bc = vect_sub(tr->c, tr->b);
	tr->ca = vect_sub(tr->a, tr->c);
	tr->n = vect_unit(cross(tr->ab, tr->bc));
	if (parse_rgb(data, &tr->rgb.r, &tr->rgb.g, &tr->rgb.b) < 0)
		return (freeturn((char **)&tr, TR));
	if (!ft_lstadd_front_o(&img->lst, ft_lstnew_id(tr, TR)))
		return (freeturn((char **)&tr, TR));
	return (INT_MIN);
}