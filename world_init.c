/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:35:10 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 08:05:50 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int		resolution_init(char *data, t_pic *img, int64_t *flag)
{
	double		width;
	double		height;
	static char	*res;

	if (!ft_isspace(*data) || flag['R']++)
		return (RES);
	res = trim_space(&data);
	width = ft_mini_atoinf(res, 'd');
	res = skip_space(data);
	height = ft_mini_atoinf(res, 'd');
	if (width == INFINITY || height == INFINITY || width <= 0 || height <= 0)
		return (RES);
	img->w = width > INT_MAX ? INT_MAX : (int)width;
	img->h = height > INT_MAX ? INT_MAX : (int)height;
	return (INT_MIN);
}

int		amb_init(char *data, t_pic *img, int64_t *flag)
{
	t_llist a;
	char	*ratio;

	if (!ft_isspace(*data) || flag['A']++)
		return (AMB);
	if (!(ratio = trim_space(&data)) ||
		(*ratio == '-' && check_range(ratio, '0') < 0) ||
		check_range(ratio, '1') < 0 ||
		(a.pow = ft_mini_atoinf(ratio, 'f')) < 0 ||
		a.pow > 1 || a.pow == INFINITY)
		return (AMB);
	if (parse_rgb(data,
		&a.rgb.r, &a.rgb.g, &a.rgb.b) < 0)
		return (AMB);
	if (!ft_lstadd_front_l(&img->amb, ft_lstnew_l(a)))
		return (AMB);
	return (INT_MIN);
}

int		cam_init(char *data, t_pic *img)
{
	t_clist	camera;

	if (!ft_isspace(*data))
		return (CAM);
	if (split_comma(trim_space(&data),
		&camera.pos.x, &camera.pos.y, &camera.pos.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&camera.n.x, &camera.n.y, &camera.n.z) < 0 ||
		(!camera.n.x && !camera.n.y && !camera.n.z))
		return (CAM);
	camera.n = vect_unit(camera.n);
	if ((camera.fov = ft_mini_atoinf(skip_space(data), 'd')) == INFINITY ||
		!(0 <= camera.fov && camera.fov <= 180))
		return (CAM);
	camera.fov = camera.fov * PI / 180;
	if (!ft_lstadd_front_c(&img->cam, ft_lstnew_c(camera)))
		return (CAM);
	return (INT_MIN);
}

int		light1_init(char *data, t_pic *img)
{
	t_llist l;
	char	*ratio;

	if (!ft_isspace(*data))
		return (LIGHT);
	if (split_comma(trim_space(&data),
		&l.pos.x, &l.pos.y, &l.pos.z) < 0)
		return (LIGHT);
	if (!(ratio = trim_space(&data)) ||
		(*ratio == '-' && check_range(ratio, '0') < 0) ||
		check_range(ratio, '1') < 0 ||
		(l.pow = ft_mini_atoinf(ratio, 'f')) < 0 || l.pow > 1)
		return (LIGHT);
	if (parse_rgb(data, &l.rgb.r, &l.rgb.g, &l.rgb.b) < 0)
		return (LIGHT);
	if (!ft_lstadd_front_l(&img->light, ft_lstnew_l(l)))
		return (LIGHT);
	return (INT_MIN);
}

double	ft_mini_atoinf(const char *s, char type)
{
	int		neg;
	size_t	len;
	double	integer;
	double	fraction;

	if (!s || (type != 'f' && type != 'd'))
		return (INFINITY);
	neg = *s == '-' ? *s++ == '-' : 0;
	if ((*s == '0' && s[1] && s[1] != '.') || !('0' <= *s && *s <= '9'))
		return (INFINITY);
	integer = 0;
	while ('0' <= *s && *s <= '9')
		integer = integer * 10 + *s++ - '0';
	if (!*s && type == 'd' && integer == INFINITY)
		return (DBL_MAX);
	if ((*s && (type == 'd' || (type == 'f' && *s != '.'))) ||
		integer == INFINITY || ((len = ft_strlen(s)) == 1))
		return (INFINITY);
	fraction = 0;
	while (*s && '0' <= s[--len] && s[len] <= '9')
		fraction = fraction / 10 + (s[len] - '0');
	if (len > 0)
		return (INFINITY);
	return (neg ? -(integer + fraction / 10) : integer + fraction / 10);
}
