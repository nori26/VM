/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/21 23:10:34 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTS_H
# define PUTS_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# define PI 3.14159265
# define GLOSS 8
# define AMB 0.001
// # define AMB 1
# define DIFF 0.69
// # define DIFF 1
// # define SPEC 0.3
# define SPEC 1

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
double			dot(t_vect v1, t_vect v2);
t_vect			cross(t_vect v1, t_vect v2);
t_vect			vect_add(t_vect v1, t_vect v2);
t_vect			vect_mult(t_vect v1, double d);
t_vect			vect_sub(t_vect v1, t_vect v2);
t_vect			point_to_vect(double x, double y, t_win win);
t_vect			vect_init(double x, double y, double z);
double			sphere(t_vect cam, t_vect ray, t_vect sp, double r);
t_vect			vect_unit(t_vect v);
int				light(t_vect point, t_vect sp, t_vect u_view);
int				spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl);


#endif