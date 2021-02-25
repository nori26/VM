/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 04:28:52 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/25 23:02:42 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_set(void *p1, void *p2)
{
	free(p1);
	return (p2);
}

int		freeturn(char **p, int ret)
{
	free(*p);
	*p = NULL;
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	return (*s == (char)c ? (char *)s : NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	char	*ret;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		while (s1[len1])
			len1++;
	if (s2)
		while (s2[len2])
			len2++;
	if (!(ret = malloc(len1 + len2 + 1)))
		return (NULL);
	tmp = ret;
	while (len1 && *s1)
		*tmp++ = *s1++;
	while (len2 && *s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (ret);
}
