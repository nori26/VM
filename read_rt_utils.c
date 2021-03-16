/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 05:31:32 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 06:46:29 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

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
