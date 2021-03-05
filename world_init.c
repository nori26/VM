/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:35:10 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/05 09:19:25 by nosuzuki         ###   ########.fr       */
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

int		check_range(char *s, char c)
{
	if (!s)
		return (-1);
	s += (*s == '-');
	if (*s++ != c)
		return (0);
	s += (*s == '.');
	while (*s)
		if (*s++ != '0')
			return (-1);
	return (0);
}

int		split_comma_normal(char *s, double *a, double *b, double *c)
{
	char **res;

	if(!(res = ft_split(s, ',')))
		return (-1);
	if (comma_count(s) != 2 || split_count(res) != 3)
		return ((int)free_all(&res) - 1);
	if ((res[0][res[0][0] == '-'] == '1' && check_range(res[0], '1') < 0) ||
		(res[1][res[1][0] == '-'] == '1' && check_range(res[1], '1') < 0) ||
		(res[2][res[2][0] == '-'] == '1' && check_range(res[2], '1') < 0))
		return ((int)free_all(&res) - 1);
	*a = ft_mini_atoinf(res[0], 'f');
	*b = ft_mini_atoinf(res[1], 'f');
	*c = ft_mini_atoinf(res[2], 'f');
	free_all(&res);
	if (*a == INFINITY || *b == INFINITY || *c == INFINITY)
		return (-1);
	// printf("%g,%g,%g  ", *a, *b, *c);
	return (0);
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
	printf("%g,%g,%g  ", *a, *b, *c);
	return (0);
}

int		parse_rgb(char *s, double *r, double *g, double *b)
{
	if (split_comma(skip_space(s), r, g, b) < 0 ||
		*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (-1);
	*r /= 255;
	*g /= 255;
	*b /= 255;
	puts("");
	return (0);
}

int		resolution_init(char *data, t_img *img, int64_t *flag)
{
	double		width;
	double		height;
	static char	*res;

	if (!ft_isspace(*data) || flag['R']++)
		return (-1);
	res = trim_space(&data);
	width = ft_mini_atoinf(res, 'd');
	res = skip_space(data);
	height = ft_mini_atoinf(res, 'd');
	if (width == INFINITY || height == INFINITY || width <= 0 || height <= 0)
		return (-1);
	img->w = width > INT_MAX ? INT_MAX : (int)width;
	img->h = height > INT_MAX ? INT_MAX : (int)height;
	img->bmp_w = width > BMP_MAX ? BMP_MAX : (int)width;
	img->bmp_h = height > BMP_MAX ? BMP_MAX : (int)height;
	printf("%d  %d\n", img->w, img->h);
	return (0);
}

int		amb_init(char *data, t_img *img, int64_t *flag)
{
	t_llist a;
	char 	*ratio;

	(void)img;
	if (!ft_isspace(*data) || flag['A']++)
		return (-1);
	if (!(ratio = trim_space(&data)) ||
		(*ratio == '-' && check_range(ratio, '0') < 0) ||
		check_range(ratio, '1') < 0 ||
		(a.pow = ft_mini_atoinf(ratio, 'f')) < 0 ||
		a.pow > 1 || a.pow == INFINITY)
		return (-1);
	printf("%.1f  ", a.pow);
	if (parse_rgb(data,
		&a.rgb.r, &a.rgb.g, &a.rgb.b) < 0)
		return (-1);
	return (0);
}

int		cam_init(char *data, t_img *img, int64_t *flag)
{
	t_clist	camera;

	if (!ft_isspace(*data))
		return (-1);
	flag['c']++;
	if (split_comma(trim_space(&data),
		&camera.pos.x, &camera.pos.y, &camera.pos.z) < 0 ||
		split_comma_normal(trim_space(&data),
		&camera.n.x, &camera.n.y, &camera.n.z) < 0 ||
		(!camera.n.x && !camera.n.y && !camera.n.z))
		return (-1);
	camera.n = vect_unit(camera.n);
	if ((camera.fov = ft_mini_atoinf(skip_space(data), 'd')) == INFINITY ||
		!(0 <= camera.fov && camera.fov <= 180))
		return (-1);
	printf("%.1500g\n", camera.fov);
	camera.fov = camera.fov * PI / 180; //rad
	if (!ft_lstadd_front_c(&img->cam, ft_lstnew_c(camera)))
		return (-1);
	return (0);
}

int		light1_init(char *data, t_img *img, int64_t *flag)
{
	t_llist l;
	char 	*ratio;

	if (!ft_isspace(*data))
		return (-1);
	flag['l']++;
	if (split_comma(trim_space(&data),
		&l.pos.x, &l.pos.y, &l.pos.z) < 0)
		return (-1);
	if (!(ratio = trim_space(&data)) ||
		(*ratio == '-' && check_range(ratio, '0') < 0) ||
		check_range(ratio, '1') < 0 ||
		(l.pow = ft_mini_atoinf(ratio, 'f')) < 0 || l.pow > 1)
		return (-1);
	printf("%g  ", l.pow);
	if (parse_rgb
		(data, &l.rgb.r, &l.rgb.g, &l.rgb.b) < 0)
		return (-1);
	if (!ft_lstadd_front_l(&img->light, ft_lstnew_l(l)))
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
