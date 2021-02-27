/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 08:43:23 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/27 19:54:13 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_set(void *p1, void *p2)
{
	free(p1);
	return (p2);
}

int		freeturn(char **p, int ret)
{
	free(*p);
	*p = NULL;
	return (ret);
}

int		check_buf(char **buf, char **line, char *p)
{
	char *tmp;

	if (p)
	{
		*p = '\0';
		if (!(*line = free_set(*line, ft_strjoin(*line, *buf))))
			return (freeturn(buf, -1));
		tmp = *buf;
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
	if (!buf && (buf = malloc((uint64_t)BUFFER_SIZE + 1)))
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
		if ((p = ft_strchr(buf, '\n')))
			return (check_buf(&buf, line, p));
		if (!(*line = free_set(*line, ft_strjoin(*line, buf))))
			return (freeturn(&buf, -1));
	}
	return (len ? freeturn(&buf, -1) : freeturn(&buf, 0));
}
