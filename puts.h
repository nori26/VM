/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/18 22:21:29 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTS_H
# define PUTS_H
# include <stdio.h>
# include <stdlib.h>
# define PI 3.14159265

typedef struct  s_data {
    void        *img;
    char        *addr;
	int			w;
	int			h;
    int         bpp;
    int         line_length;
    int         endian;
	void		*mlx;
	void		*win;
}               t_data;

typedef struct	s_point
{
	double 		x;
	double		y;
	double		z;
}				t_point;
typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
	double		len;
}				t_vect;
//win minus or int_max
typedef struct	s_win
{
	int			w;
	int			h;
}				t_win;
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
int             close2(int keycode, t_data *vars);
int             close1(int keycode, t_data *vars);
double			inner(t_vect v1, t_vect v2);
t_vect			cross(t_vect v1, t_vect v2);
t_vect			vect_add(t_vect v1, t_vect v2);
t_vect			vect_mult(t_vect v1, double d);
t_vect			vect_sub(t_vect v1, t_vect v2);
t_vect			point_to_vect(double x, double y, t_win win);
t_vect			vect_init(double x, double y, double z);
int				sphere(t_vect cam, t_vect ray, t_vect sp, double r);



#endif