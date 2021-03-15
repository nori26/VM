/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:30:49 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 17:03:52 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

char	*put_message(int num)
{
	char *msg[20];

	msg[SP] = "sphere ";
	msg[PL] = "plane ";
	msg[SQ] = "square ";
	msg[CY] = "cylinder ";
	msg[TR] = "trinagle ";
	msg[CAM] = "camera ";
	msg[LIGHT] = "light ";
	msg[AMB] = "ambient ";
	msg[RES] = "resolution ";
	return (msg[num]);
}

void	err_message(int num)
{
	char *s;

	write(STDERR_FILENO, "Error\n", 7);
	if (!errno)
	{
		write(2, s = put_message(num), ft_strlen(s));
		write(2, "input error", 11);
	}
	else
		write(2, s = strerror(errno), ft_strlen(s));
}

int		lst_free(t_pic *img)
{
	void *tmp;

	while (img->lst)
	{
		tmp = img->lst->next;
		free(img->lst);
		img->lst = tmp;
	}
	while (img->light)
	{
		tmp = img->light->next;
		free(img->light);
		img->lst = tmp;
	}
	while (img->cam)
	{
		tmp = img->cam->next;
		mlx_destroy_image(img->mlx, img->cam->img);
		
	}
}