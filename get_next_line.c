/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 08:43:23 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/25 23:26:46 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_buf(char **buf, char **line, char *p)
{
	char *tmp;

	tmp = *buf;
	if (p)
	{
		*p = '\0';
		if (!(*line = free_set(*line, ft_strjoin(*line, *buf))))
			return (freeturn(buf, -1));
		while (*++p)
			*tmp++ = *p;
		*tmp = '\0';
		return (1);
	}
	else if (!(*line = free_set(*line, ft_strjoin(*line, *buf))))
		return (freeturn(buf, -1));
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		*p;
	int64_t		len;
	static char	*buf;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE == SIZE_MAX || !line)
		return (-1);
	*line = NULL;
	if (!buf && !!(buf = malloc((uint64_t)BUFFER_SIZE + 1)))
		*buf = '\0';
	if (!buf)
		return (-1);
	if ((ret = check_buf(&buf, line, ft_strchr(buf, '\n'))))
		return (ret);
	while (1)
	{
		if ((len = read(fd, buf, BUFFER_SIZE)) < 1)
			break ;
		buf[len] = '\0';
		if (!!(p = ft_strchr(buf, '\n')))
			return (check_buf(&buf, line, p));
		if (!(*line = free_set(*line, ft_strjoin(*line, buf))))
			return (freeturn(&buf, -1));
	}
	return (len ? -1 : freeturn(&buf, 0));
}
