/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:30:40 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/06 22:20:16 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t l;

	if (!*little)
		return ((char *)big);
	i = 0;
	l = ft_strlen(little);
	while (big[i] && i + l - 1 < len)
		if (!(ft_strncmp(&big[i++], little, l)))
			return ((char *)&big[--i]);
	return (NULL);
}
