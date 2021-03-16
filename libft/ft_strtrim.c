/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 05:17:05 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/06 23:10:23 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ret;
	int		ascii[256];

	if (!s1 || !set)
		return (!s1 ? NULL : ft_strdup(s1));
	ft_bzero(ascii, sizeof(ascii));
	while (*set)
		ascii[(int)*set++] += 1;
	while (*s1 && ascii[(int)*s1])
		s1++;
	len = ft_strlen(s1);
	while (len && ascii[(int)*(s1 + len - 1)])
		len--;
	if (!(ret = malloc(len + 1)))
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}
