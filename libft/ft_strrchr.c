/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:36:23 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/22 21:32:54 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t l;

	l = ft_strlen(s) + 1;
	while (l)
		if (*(s + --l) == (char)c)
			return ((char *)s + l);
	return (NULL);
}
