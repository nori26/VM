/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 06:54:19 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/25 21:12:23 by nosuzuki         ###   ########.fr       */
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
int		check_buf(char **buf, char **line, char *p);
#endif
