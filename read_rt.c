/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:50:38 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/15 19:47:38 by nosuzuki         ###   ########.fr       */
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
		return (INT_MIN);
	return (-2);
}

int		parse_rt(t_pic *img, char *path)
{
	int			fd;
	int			res;
	int			tmp;
	char		*data;
	int64_t		flag[130];

	if ((fd = open(path, O_RDONLY)) < 0)
		err_exit(img, -3);
	res = 1;
	ft_bzero(flag, sizeof(flag));
	while (res == 1)
	{
		tmp = res;
		res = get_next_line(fd, &data);
		if ((tmp && !res && !*data) || (!flag[0]++ && !*data))
			return (freeturn(&data, -2));
		if ((tmp = make_obj(data, img, flag)) != INT_MIN)
			return (freeturn(&data, tmp));
		free(data);
	}
	if (flag['R'] != 1)
		return (RES);
	if (flag['A'] != 1)
		return (AMB);
	return (INT_MIN);
}

void		read_rt(t_pic *img, char *path)
{
	int		res;
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || path[len - 4] == '/' || ft_strncmp(path + len - 3, ".rt", 3))
		err_exit(img, -2);
	if ((res = parse_rt(img, path)) != INT_MIN)
		err_exit(img, res);
	img->o_start = img->lst;
	img->c_start = img->cam;
	img->l_start = img->light;
}