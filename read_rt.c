/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:50:38 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/25 21:10:08 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int		make_obj(char *data)
{
	if (data[0] == 'R')
		resolution_init(data);
	else if (data[0] == 'A')
		amb_init(data);
	else if (data[0] == 'c' && data[1] == 'y')
		cy_init(data);
	else if (data[0] == 'c')
		cam_init(data);
	else if (data[0] == 'l')
		light_init(data);
	else if (data[0] == 'p' && data[1] == 'l')
		pl_init(data);
	else if (data[0] == 's' && data[1] == 'p')
		sp_init(data);
	else if (data[0] == 's' && data[1] == 'q')
		sq_init(data);
	else if (data[0] == 't' && data[1] == 'r')
		tr_init(data);
	else if (data[0] == '\n')
		return (0);
	else
		return (-1);

}

int		read_rt(char *path)
{
	int		fd;
	int		res;
	char	*data;

	res = 1;
	fd = open(path, O_RDONLY);
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		if (make_obj(data) < 0)
			return (-1);
		free(data);
	}
	return (-1);
}