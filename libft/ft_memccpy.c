/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 02:07:32 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/22 21:15:19 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	unsigned char const *s;

	d = dest;
	s = src;
	while (n--)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return (d);
	}
	return (NULL);
}
