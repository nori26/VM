/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:35:10 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/28 00:01:26 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"
#include "mlx.h"

int		ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

char	*skip_space(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (s);
}

char	*skip_not_space(char *s)
{
	while (*s && !ft_isspace(*s))
		s++;
	return (s);
}

char	*trim_space(char **s)
{
	char	*tmp;
	char	*ret;

	ret = skip_space(*s);
	if (!*(tmp = skip_not_space(ret)))
		return (NULL);
	*tmp = '\0';
	*s = ++tmp;
	return (ret);
}

int		comma_count(char *s)
{
	int	count;

	count = 0;
	while (*s && count != INT_MAX)
		if (*s++ == ',')
			count++;
	return (count);
}

int		split_count(char **s)
{
	int i;

	i = 0;
	while (s[i] && i != INT_MAX)
		i++;
	return (i);
}

int		split_comma(char *s, double *a, double *b, double *c)
{
	char **status;

	if(!(status = ft_split(s, ',')))
		return (-1);
	if (comma_count(s) != 2 || split_count(status) != 3)
		return ((int)free_all(&status) - 1);
	*a = ft_mini_atoinf(status[0], 'f');
	*b = ft_mini_atoinf(status[1], 'f');
	*c = ft_mini_atoinf(status[2], 'f');
	free_all(&status);
	if (*a == INFINITY || *b == INFINITY || *c == INFINITY)
		return (-1);
	return (0);
}

int		parse_rgb(char *s, double *r, double *g, double *b)
{
	if (split_comma(skip_space(s), r, g, b) < 0 ||
		*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (-1);
	printf("%g,%g,%g\n", *r, *g, *b);
	*r /= 255;
	*g /= 255;
	*b /= 255;
	return (0);
}

int		resolution_init(char *data, t_img *img)
{
	int 		win_w;
	int 		win_h;
	double		width;
	double		height;
	static char	*res;

	if (!ft_isspace(*data) || res)
		return (-1);
	res = trim_space(&data);
	width = ft_mini_atoinf(res, 'd');
	res = skip_space(data);
	height = ft_mini_atoinf(res, 'd');
	if (width > INT_MAX || height > INT_MAX || width <= 0 || height <= 0)
		return (-1);
	win_w = 512;
	win_h = 512;
	// mlx_get_screen_size(img->mlx, &x, &y);
	img->w = width > win_w ? win_w : (int)width;
	img->h = height > win_h ? win_h : (int)height;
	printf("%d  %d\n", img->w, img->h);
	return (0);
}

int		amb_init(char *data, t_img *img)
{
	static int i;

	if (!ft_isspace(*data) || i)
		return (-1);
	i++;
	if ((img->amb.pow = ft_mini_atoinf(trim_space(&data), 'f')) < 0 ||
		img->amb.pow > 1 || img->amb.pow == INFINITY)
		return (-1);
	printf("%.1f  ", img->amb.pow);
	if (parse_rgb(data,
		&img->amb.rgb.r, &img->amb.rgb.g, &img->amb.rgb.b) < 0)
		return (-1);
	return (0);
}

int		cam_init(char *data, t_img *img)
{
	double	fov;
	char	*res;
	char	**status;

	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->cam.x, &img->cam.y, &img->cam.z) < 0 ||
		split_comma(trim_space(&data),
		&img->cam_normal.x, &img->cam_normal.y, &img->cam_normal.z) < 0)
		return (-1);
	//normal == 0;
	printf("%.1f,%.1f,%.1f  ", img->cam.x,img->cam.y,img->cam.z);
	printf("%.1f,%.1f,%.1f  ", img->cam_normal.x,img->cam_normal.y,img->cam_normal.z);
	if ((fov = ft_mini_atoinf(skip_space(data), 'd')) == INFINITY ||
		!(0 <= fov && fov <= 180))
		return (-1);
	img->fov = (int)fov;
	printf("%d\n", img->fov);
	return (0);
}

int		light1_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	if (split_comma(trim_space(&data),
		&img->light.pos.x, &img->light.pos.y, &img->light.pos.z) < 0)
		return (-1);
	printf("%g,%g,%g  ", img->light.pos.x,img->light.pos.y,img->light.pos.z);
	if ((img->light.pow = ft_mini_atoinf(trim_space(&data), 'f')) < 0 ||
		img->light.pow > 1 || img->light.pow == INFINITY)
		return (-1);
	printf("%g  ", img->light.pow);
	if (parse_rgb
		(data, &img->light.rgb.r, &img->light.rgb.g, &img->light.rgb.b) < 0)
		return (-1);
	return (0);
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
