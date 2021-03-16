/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 04:11:35 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/07 08:16:58 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char c)
{
	long i;
	long len;
	char **ret;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	len = !!s[i] + 1;
	while (s[i])
		len += (s[i++] == c && s[i] != c && s[i]);
	if (!(ret = malloc(sizeof(char *) * len)))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (((len = ft_strchr(s, c) - s) &&
			!(ret[i] = ft_substr(s, 0, len > 0 ? (size_t)len : ft_strlen(s)))))
			return (free_all(&ret));
		s += len ? ft_strlen(ret[i]) : 1;
		i += !!len;
	}
	ret[i] = 0;
	return (ret);
}
