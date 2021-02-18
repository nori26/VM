/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/18 01:02:30 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTS_H
# define PUTS_H
# include <stdio.h>
# include <stdlib.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bpp;
    int         line_length;
    int         endian;
	void		*mlx;
	void		*win;
}               t_data;
typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
int             close2(int keycode, t_data *vars);
int             close1(int keycode, t_data *vars);
double			inner(t_vec v1, t_vec v2);
t_vec			outer(t_vec v1, t_vec v2);







#endif