/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:32:37 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/02 03:16:24 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int	pl_init(char *data, t_img *img)
{
	t_pl *pl;

	if (!ft_isspace(*data))
		return (-1);
	if (!(pl = malloc(sizeof(t_pl))))
		return (-1);
	if (split_comma(trim_space(&data),
		&pl->p.x, &pl->p.y, &pl->p.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&pl->n.x, &pl->n.y, &pl->n.z) < 0 ||
		(!pl->n.x && !pl->n.y && !pl->n.z))
		return (freeturn((char **)&pl, -1));
	if (parse_rgb(data, &pl->rgb.r, &pl->rgb.g, &pl->rgb.b) < 0)
		return (freeturn((char **)&pl, -1));
	if (!ft_lstadd_front_rt(&img->lst, ft_lstnew_rt(pl, plane)))
		return (freeturn((char **)&pl, -1));
	return (0);
}
int	sp1_init(char *data, t_img *img)
{
	t_sp	*sp;

	if (!ft_isspace(*data))
		return (-1);
	if (!(sp = malloc(sizeof(t_sp))))
		return (-1);
	if (split_comma(trim_space(&data),
		&sp->o.x, &sp->o.y, &sp->o.z) < 0)
		return (freeturn((char **)&sp, -1));
	if ((sp->r = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		sp->r == INFINITY)
		return (freeturn((char **)&sp, -1));
	printf("%g  ", sp->r);
	sp->r /= 2;
	if (parse_rgb(data, &sp->rgb.r, &sp->rgb.g, &sp->rgb.b) < 0)
		return (freeturn((char **)&sp, -1));
	if (!ft_lstadd_front_rt(&img->lst, ft_lstnew_rt(sp, sphere)))
		return (freeturn((char **)&sp, -1));
	return (0);
}

int	sq_init(char *data, t_img *img)
{
	t_sq *sq;

	if (!ft_isspace(*data))
		return (-1);
	if (!(sq = malloc(sizeof(t_sq))))
		return (-1);
	if (split_comma(trim_space(&data), &sq->p.x, &sq->p.y, &sq->p.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&sq->n.x, &sq->n.y, &sq->n.z) < 0 || (!sq->n.x && !sq->n.y && !sq->n.z))
		return (freeturn((char **)&sq, -1));
	if ((sq->size = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		sq->size == INFINITY)
		return (freeturn((char **)&sq, -1));
	printf("%g  ", sq->size);
	if (parse_rgb(data, &sq->rgb.r, &sq->rgb.g, &sq->rgb.b) < 0)
		return (freeturn((char **)&sq, -1));
	if (!ft_lstadd_front_rt(&img->lst, ft_lstnew_rt(sq, square)))
		return (freeturn((char **)&sq, -1));
	return (0);
}

int	cy_init(char *data, t_img *img)
{
	t_cy *cy;

	if (!ft_isspace(*data))
		return (-1);
	if (!(cy = malloc(sizeof(t_cy))))
		return (-1);
	if (split_comma(trim_space(&data), &cy->p.x, &cy->p.y, &cy->p.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&cy->n.x, &cy->n.y, &cy->n.z) < 0 || (!cy->n.x && !cy->n.y && !cy->n.z))
		return (freeturn((char **)&cy, -1));
	if ((cy->r = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		cy->r == INFINITY)
		return (freeturn((char **)&cy, -1));
	printf("%g  ", cy->r);
	cy->r /= 2;
	if ((cy->h = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		cy->h == INFINITY)
		return (freeturn((char **)&cy, -1));
	printf("%g  ", cy->h);
	if (parse_rgb(data, &cy->rgb.r, &cy->rgb.g, &cy->rgb.b) < 0)
		return (freeturn((char **)&cy, -1));
	if (!ft_lstadd_front_rt(&img->lst, ft_lstnew_rt(cy, cylinder)))
		return (freeturn((char **)&cy, -1));
	return (0);
}

int	tr_init(char *data, t_img *img)
{
	t_tr *tr;

	if (!ft_isspace(*data))
		return (-1);
	if (!(tr = malloc(sizeof(t_tr))))
		return (-1);
	if (split_comma(trim_space(&data), &tr->o.x, &tr->o.y, &tr->o.z) < 0 ||
		split_comma(trim_space(&data), &tr->p.x, &tr->p.y, &tr->p.z) < 0 ||split_comma(trim_space(&data), &tr->q.x, &tr->q.y, &tr->q.z) < 0)
		return (freeturn((char **)&tr, -1));
	
	if (parse_rgb(data, &tr->rgb.r, &tr->rgb.g, &tr->rgb.b) < 0)
		return (freeturn((char **)&tr, -1));
	if (!ft_lstadd_front_rt(&img->lst, ft_lstnew_rt(tr, triangle)))
		return (freeturn((char **)&tr, -1));
	return (0);
}