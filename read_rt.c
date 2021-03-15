/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:50:38 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 08:40:43 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puts.h"

int		make_obj(char *data, t_pic *img, int64_t *flag)
{
	if (data[0] == 'R')
		return(resolution_init(++data, img, flag));
	else if (data[0] == 'A')
		return(amb_init(++data, img, flag));
	else if (data[0] == 'c' && data[1] == 'y')
		return(cy_init(data + 2, img));
	else if (data[0] == 'c')
		return(cam_init(++data, img, flag));
	else if (data[0] == 'l')
		return(light1_init(++data, img, flag));
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

int		parse_rt(t_pic *img, char *path)
{
	int			fd;
	int			res;
	int			tmp;
	char		*data;
	int64_t		flag[130];

	if ((fd = open(path, O_RDONLY)) < 0)
		return (printf("error\n") - 10);//
	res = 1;
	ft_bzero(flag, sizeof(flag));
	while (res == 1)
	{
		tmp = res;
		res = get_next_line(fd, &data);
		if ((tmp && !res && !*data) || (!flag[0]++ && !*data))
			return (freeturn(&data, -1));
		if (make_obj(data, img, flag) < 0)
			return (freeturn(&data, -1));
		free(data);
	}
	if (flag['R'] != 1 || flag['A'] > 1)
		return (-1);
	if (!flag['c'])
		return (0); //after
	if (!flag['l'])
		return (0); //after
	return (0);
}

void		read_rt(t_pic *img, char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || path[len - 4] == '/' ||
		ft_strncmp(path + len - 3, ".rt", 3) ||
		parse_rt(img, path) < 0)
		exit(1);
	img->o_start = img->lst;
	img->c_start = img->cam;
	img->l_start = img->light;
}