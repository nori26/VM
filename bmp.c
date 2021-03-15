/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:55:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 18:30:00 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"
#include "mlx.h"

void	file_header(t_pic *img, int fd)
{
	uint32_t size;

	size = img->w * img->h * 4 + 14 + 12;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0", 2);
	write(fd, "\0\0", 2);
	size = 14 + 12;
	write(fd, &size, 4);
}

void	info_header(t_pic *img, int fd)
{
	uint32_t info;
	uint32_t plane;
	uint32_t bpp;

	info = 12;
	write(fd, &info, 4);
	write(fd, &img->w, 2);
	write(fd, &img->h, 2);
	plane = 1;
	write(fd, &plane, 2);
	bpp = 32;
	write(fd, &bpp, 2);
}

void	image_data(t_pic *img, int fd)
{
	int			x;
	int			y;
	uint32_t	*buf;
	uint32_t	*tmp;

	if (!(buf = malloc(img->w * img->h * 4)))
		err_exit(img, 0);
	x = 0;
	y = img->h - 1;
	tmp = buf;
	while (y >= 0)
	{
		x = 0;
		while (x < img->w)
		{
			*tmp = *(int *)(img->cam->adr +
			(y * img->width_bytes + x * (img->bpp / 8)));
			tmp++;
			x++;
		}
		y--;
	}
	write(fd, buf, img->w * img->h * 4);
	free(buf);
}

int		bmp(t_pic *img)
{
	int fd;

	if (!img->cam)
		err_exit(img, CAM);
	if ((fd = open("miniRT.bmp",
		O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		err_exit(img, 0);
	if (img->w > BMP_MAX)
		img->w = BMP_MAX;
	if (img->h > BMP_MAX)
		img->h = BMP_MAX;
	file_header(img, fd);
	info_header(img, fd);
	image_data(img, fd);
	close(fd);
	return (0);
}