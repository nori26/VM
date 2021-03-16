/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:23:00 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/11/02 02:43:54 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_all(char **ret)
{
	size_t i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		ret[i++] = 0;
	}
	free(ret);
}

static size_t	split(char **ret, char *cpy, size_t len)
{
	size_t i;
	size_t n;

	n = 0;
	while (len)
	{
		i = 0;
		while (cpy[i] == '\0' && i < len)
			i++;
		cpy += i;
		if (*cpy && !(ret[n++] = ft_strdup(cpy)))
			break ;
		len -= (ft_strlen(cpy) + i);
		cpy += ft_strlen(cpy);
	}
	if (len)
		return (0);
	ret[n] = 0;
	return (1);
}

static size_t	ft_null(char *cpy, char c)
{
	size_t	n;
	char	*tmp;

	n = 0;
	tmp = cpy;
	while (*tmp)
	{
		while (*tmp && *tmp == c)
			tmp++;
		while (*tmp && *tmp != c)
			tmp++;
		n++;
	}
	if (n == 0)
		n++;
	if (n > 1 && *--tmp == c)
		n--;
	while (*cpy)
		if (*cpy++ == c)
			*(cpy - 1) = '\0';
	return (n);
}

char			**ft_split(char const *s, char c)
{
	size_t	n;
	size_t	len;
	char	*cpy;
	char	**ret;

	if (!s || !(cpy = ft_strdup(s)))
		return (NULL);
	len = ft_strlen(cpy);
	n = ft_null(cpy, c);
	if (!(ret = malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	if (!(split(ret, cpy, len)))
	{
		free(cpy);
		free_all(ret);
		return (NULL);
	}
	free(cpy);
	return (ret);
}
