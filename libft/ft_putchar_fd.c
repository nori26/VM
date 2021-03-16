/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:02:09 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/06 21:16:14 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char c1;
	unsigned char b1;
	unsigned char b2;

	if ((unsigned char)c < 128)
		write(fd, &c, 1);
	else
	{
		c1 = c;
		b1 = 0b11000000;
		b2 = 0b10000000;
		b1 += c1 >> 6;
		b2 += c1 - (b1 << 6);
		write(fd, &b1, 1);
		write(fd, &b2, 1);
	}
}
