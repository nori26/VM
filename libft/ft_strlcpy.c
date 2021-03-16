/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:01:31 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/21 02:52:27 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	if (!src)
		return (len);
	while (src[len])
		len++;
	if (!size || !dst)
		return (len);
	while (i < size - 1 && i++ < len)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}
