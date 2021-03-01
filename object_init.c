/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:32:37 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/01 18:56:06 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int	pl_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->cam.x, &img->cam.y, &img->cam.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&img->cam_normal.x, &img->cam_normal.y, &img->cam_normal.z) < 0 ||
		(!img->cam_normal.x && !img->cam_normal.y && !img->cam_normal.z))
		return (-1);
	printf("%.1f,%.1f,%.1f  ", img->cam.x,img->cam.y,img->cam.z);
	printf("%.1f,%.1f,%.1f  ", img->cam_normal.x,img->cam_normal.y,img->cam_normal.z);
	if (parse_rgb
		(data, &img->light.rgb.r, &img->light.rgb.g, &img->light.rgb.b) < 0)
		return (-1);
	return (0);
}
int	sp1_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->light.pos.x, &img->light.pos.y, &img->light.pos.z) < 0)
		return (-1);
	printf("%g,%g,%g  ", img->light.pos.x,img->light.pos.y,img->light.pos.z);
	if ((img->light.pow = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		img->light.pow == INFINITY)
		return (-1);
	printf("%g  ", img->light.pow);
	if (parse_rgb
		(data, &img->light.rgb.r, &img->light.rgb.g, &img->light.rgb.b) < 0)
		return (-1);
	return (0);
}
int	sq_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->cam.x, &img->cam.y, &img->cam.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&img->cam_normal.x, &img->cam_normal.y, &img->cam_normal.z) < 0 ||
		(!img->cam_normal.x && !img->cam_normal.y && !img->cam_normal.z))
		return (-1);
	printf("%.1f,%.1f,%.1f  ", img->cam.x,img->cam.y,img->cam.z);
	printf("%.1f,%.1f,%.1f  ", img->cam_normal.x,img->cam_normal.y,img->cam_normal.z);
	if ((img->light.pow = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		img->light.pow == INFINITY)
		return (-1);
	printf("%g  ", img->light.pow);
	if (parse_rgb
		(data, &img->light.rgb.r, &img->light.rgb.g, &img->light.rgb.b) < 0)
		return (-1);
	return (0);
}
int	cy_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->cam.x, &img->cam.y, &img->cam.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&img->cam_normal.x, &img->cam_normal.y, &img->cam_normal.z) < 0 ||
		(!img->cam_normal.x && !img->cam_normal.y && !img->cam_normal.z))
		return (-1);
	printf("%.1f,%.1f,%.1f  ", img->cam.x,img->cam.y,img->cam.z);
	printf("%.1f,%.1f,%.1f  ", img->cam_normal.x,img->cam_normal.y,img->cam_normal.z);
	if ((img->light.pow = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		img->light.pow == INFINITY)
		return (-1);
	printf("%g  ", img->light.pow);
	if ((img->light.pow = ft_mini_atoinf(trim_space(&data), 'f')) <= 0 ||
		img->light.pow == INFINITY)
		return (-1);
	printf("%g  ", img->light.pow);
	if (parse_rgb
		(data, &img->light.rgb.r, &img->light.rgb.g, &img->light.rgb.b) < 0)
		return (-1);
	return (0);
}
int	tr_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->cam.x, &img->cam.y, &img->cam.z) < 0)
	return (0);
}