/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:30:49 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 17:44:17 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

char	*err_message(int num)
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

void	err_exit(t_pic *img, int num)
{
	char *s;

	write(STDERR_FILENO, "Error\n", 7);
	if (!errno)
	{
		write(STDERR_FILENO, s = err_message(num), ft_strlen(s));
		write(STDERR_FILENO, "input error", 11);
	}
	else
		write(STDERR_FILENO, s = strerror(errno), ft_strlen(s));
	close_img(img);
	exit(1);
}

void	*lst_free(void *lst, void *next)
{
	free(lst);
	return (next);
}

void	close_img(t_pic *img)
{
	while (img->lst)
		img->lst = lst_free(img->lst, img->lst->next);
	while (img->light)
		img->light = lst_free(img->light, img->light->next);
	while (1)
	{
		mlx_destroy_image(img->mlx, img->cam->img);
		img->cam = lst_free(img->cam, img->cam->next);
		if (img->cam == img->c_start)
			break ;
	}
}