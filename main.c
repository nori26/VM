/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:55:51 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 07:15:50 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int		main_loop(t_pic *img)
{
	mlx_put_image_to_window(img->mlx, img->win, img->cam->img, 0, 0);
	return (0);
}

void	window(t_pic *img)
{
	img->win = mlx_new_window(img->mlx, img->w, img->h, "miniRT");
	mlx_hook(img->win, 2, 1, close2, img);
	mlx_hook(img->win, 33, 1 << 17, close1, img);
	if (img->cam)
		mlx_loop_hook(img->mlx, &main_loop, img);
    mlx_loop(img->mlx);
}

void	img_size(t_pic *img)
{
	int w;
	int h;

	if (img->bmp)
	{
		if (img->w > BMP_MAX)
			img->w = BMP_MAX;
		if (img->h > BMP_MAX)
			img->h = BMP_MAX;
	}
	else
	{
		mlx_get_screen_size(img->mlx, &w, &h);
		if (img->w > w)
			img->w = w;
		if (img->h > h)
			img->h = h;
	}
}

void	draw_img(t_pic *img)
{
    img->mlx = mlx_init();
	img_size(img);
	func_ary_init(img);
	ray_trace(img);
	if (img->bmp)
		bmp(img);
	else
		window(img);
}

int     main(int argc, char *argv[])
{
	t_pic 	img;

	errno = 0;
	ft_bzero(&img, sizeof(img));
	if ((argc != 2 && argc != 3) ||
		(argc > 2 && !(img.bmp += !ft_strncmp(argv[2], "--save", 7))))
		err_exit(&img, -1);
	read_rt(&img, argv[1]);
	draw_img(&img);
}
