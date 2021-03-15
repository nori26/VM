/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:30:49 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 21:41:02 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

void	err_exit(t_pic *img, int num)
{
	char *s;

	//num == CY,0 改行終端, -1
	write(STDERR_FILENO, "Error\n", 7);
	if (errno)
	{
		s = strerror(errno);
		write(STDERR_FILENO, s, ft_strlen(s));
	}
	else if (num >= 0)
	{
		s = err_message(num);
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, "input error\n", 12);
	}
	else if (num == -1)
		write(STDERR_FILENO, "argument error\n", 15);
	else if (num == -2)
		write(STDERR_FILENO, "rt format error\n", 16);
	else
		write(STDERR_FILENO, "unknown error\n", 14);
	close_img(img);
	exit(1);
}

char	*err_message(int num)
{
	char *msg[10];

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

void	*lst_free(void *lst, void *next, void *content)
{
	free(lst);
	free(content);
	return (next);
}

void	close_img(t_pic *img)
{
	free(img->amb);
	img->lst = img->o_start;
	img->light = img->l_start;
	img->cam = img->c_start;
	while (img->lst)
		img->lst = lst_free(img->lst, img->lst->next, img->lst->obj);
	while (img->light)
		img->light = lst_free(img->light, img->light->next, 0);
	while (1)
	{
		if (!img->cam)
			break;
		if (img->cam && img->mlx && img->cam->img)
			mlx_destroy_image(img->mlx, img->cam->img);
		img->cam = lst_free(img->cam, img->cam->next, 0);
		if (img->cam == img->c_start)
			break ;
	}
	if (img->mlx && img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
		mlx_destroy_display(img->mlx);
	free(img->mlx);
}
