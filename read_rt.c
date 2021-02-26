/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:50:38 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/26 19:20:04 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int		make_obj(char *data, t_img *img)
{
	if (data[0] == 'R')
		return(resolution_init(++data, img));
	else if (data[0] == 'A')
		return(amb_init(++data, img));
	else if (data[0] == 'c' && data[1] == 'y')
		return(cy_init(data + 2, img));
	else if (data[0] == 'c')
		return(cam_init(++data, img));
	else if (data[0] == 'l')
		return(light1_init(++data, img));
	else if (data[0] == 'p' && data[1] == 'l')
		return(pl_init(data + 2, img));
	else if (data[0] == 's' && data[1] == 'p')
		return(sp1_init(data + 2, img));
	else if (data[0] == 's' && data[1] == 'q')
		return(sq_init(data + 2, img));
	else if (data[0] == 't' && data[1] == 'r')
		return(tr_init(data + 2, img));
	else if (!data[0])
		return (0);
	return (-1);
}

int		read_rt(char *path, t_img *img)
{
	int		fd;
	int		res;
	char	*data;

	res = 1;
	fd = open(path, O_RDONLY);
	while (res == 1)
	{
		res = get_next_line(fd, &data);
		if (make_obj(data, img) < 0)
			return (freeturn(&data, -1));
		free(data);
	}
	return (-1);
}

int main(int argc, char *argv[])
{
	t_img img;

	if (argc != 2)
		return (-1);
	read_rt(argv[1], &img);
}