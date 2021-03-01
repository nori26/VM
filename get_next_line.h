/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 06:54:19 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/01 22:50:40 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include "libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# define BUF_SIZE BUFFER_SIZE
int		get_next_line(int fd, char **line);
int		check_buf(char **buf, char **line, char *p);
int		freeturn(char **p, int ret);
void	*free_set(void *p1, void *p2);
#endif
