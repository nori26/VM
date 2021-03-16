/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 05:33:40 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 08:03:48 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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

	if (!(res = ft_split(s, ',')))
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
	return (0);
}

int		split_comma(char *s, double *a, double *b, double *c)
{
	char **status;

	if (!(status = ft_split(s, ',')))
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
	*r /= 255;
	*g /= 255;
	*b /= 255;
	return (0);
}
