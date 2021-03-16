/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:19:45 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/22 20:39:02 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char const *a;
	unsigned char const	*b;

	a = s1;
	b = s2;
	while (n && *a++ == *b++)
		n--;
	return ((n == 0) ? 0 : *--a - *--b);
}
