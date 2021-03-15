/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:55:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 08:03:03 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"
#include "mlx.h"

int	bmp(t_pic *img)
{
	int x;
	int y;
	int fd;
	uint32_t size;
	uint32_t info;

	if (!img->cam)
		exit(1);
	if ((fd = open("miniRT.bmp",
		O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO) == -1))
		exit(1);
	if (img->w > BMP_MAX)
		img->w = BMP_MAX;
	if (img->h > BMP_MAX)
		img->h = BMP_MAX;
	func_ary_init(img);
	ray_trace(img);
	size = img->w * img->h * 4 + 14 + 12;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0", 2);
	write(fd, "\0\0", 2);
	size = 14 + 12;
	write(fd, &size, 4);
	info = 12;
	write(fd, &info, 4);
	write(fd, &img->w, 4);
	write(fd, &img->h, 4);
	info = 1;
	write(fd, &info, 2);
	info = 32;
	write(fd, &info, 4);
	x = 0;
	y = 0;
	while (x < img->h * img->w * 4)
	{
		write(fd, img->cam->addr + x++, 1);
	}
	// write(fd, , );
	// write(fd, , );
	// write(fd, , );
	// write(fd, , );
	// write(fd, , );
	// write(fd, , );
	return (0);
}