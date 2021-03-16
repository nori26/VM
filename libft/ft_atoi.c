/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 03:14:09 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/11 19:37:15 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char		neg;
	uint64_t	num;

	num = 0;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	neg = (*str == '+' || *str == '-') ? *str++ == '-' : 0;
	while ('0' <= *str && *str <= '9')
		if (num >> 60 || (num = num * 10 + *str++ - '0') >> 63)
			return (num = neg ? LONG_MIN : LONG_MAX);
	return (neg ? -num : num);
}
