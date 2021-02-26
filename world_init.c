/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:35:10 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/26 23:13:30 by nosuzuki         ###   ########.fr       */
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
	tmp = skip_not_space(ret);
	*tmp = '\0';
	*s = ++tmp;
	return (ret);
}

int		resolution_init(char *data, t_img *img)
{
	int 	win_w;
	int 	win_h;
	char	*res;
	double	width;
	double	height;

	if (!ft_isspace(*data))
		return (-1);
	res = trim_space(&data);
	width = ft_mini_atoinf(res, 'd');
	res = trim_space(&data);
	height = ft_mini_atoinf(res, 'd');
	if (width > INT_MAX || height > INT_MAX || width < 0 || height < 0)
		return (-1);
	win_w = 512;
	win_h = 512;
	// mlx_get_screen_size(img->mlx, &x, &y);
	img->w = width > win_w ? win_w : width;
	img->h = height > win_h ? win_h : height;
	printf("%d\n%d\n", img->w, img->h);
	return (0);
}

int		amb_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	return (0);
}

int		cam_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	
	return (0);
}

int		light1_init(char *data, t_img *img)
{
	if (!ft_isspace(*data))
		return (-1);
	return (0);
}

double	ft_mini_atoinf(const char *s, char type)
{
	int		neg;
	size_t	len;
	double	integer;
	double	fraction;

	if (!s)
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
