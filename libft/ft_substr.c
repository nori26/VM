/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 21:32:54 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/30 17:04:48 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	slen;

	if (!s || !len)
		return (ft_strdup(""));
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	len = (slen - start < len) ? slen - start : len;
	if (!(dest = malloc(len + 1)))
		return (NULL);
	ft_strlcpy(dest, s + start, len + 1);
	return (dest);
}
