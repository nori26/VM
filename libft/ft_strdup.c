/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:58:34 by nosuzuki          #+#    #+#             */
/*   Updated: 2020/10/18 02:23:32 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *dest;
	char *ret;

	if (!(dest = malloc(ft_strlen(s) + 1)))
		return (NULL);
	ret = dest;
	while (*s)
		*dest++ = *s++;
	*dest = '\0';
	return (ret);
}
