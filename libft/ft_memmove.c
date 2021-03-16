/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 05:32:43 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/20 22:56:19 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *d;

	d = dest;
	if (!n || dest == src)
		return (dest);
	if (src > dest)
		while (n--)
			*d++ = *(unsigned char *)src++;
	else
		while (n--)
			d[n] = ((unsigned char *)src)[n];
	return (dest);
}
