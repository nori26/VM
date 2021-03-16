/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:10:48 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/01/13 06:32:55 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	nbr(long n, char sign, char **ret, int len)
{
	len++;
	if (n > 9 && (len = nbr(n / 10, sign, ret, len)) < 0)
		return (-1);
	if (n < 10)
	{
		if (!(*ret = malloc(len + sign + 1)))
			return (-1);
		(*ret)[len + sign] = '\0';
		len = 0;
		if (sign)
			(*ret)[len++] = '-';
	}
	(*ret)[len++] = n % 10 + '0';
	return (len);
}

char		*ft_itoa(int n)
{
	char	*ret;

	if (nbr(n < 0 ? -(long)n : n, n < 0, &ret, 0) < 0)
		return (NULL);
	return (ret);
}
