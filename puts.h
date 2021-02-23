/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/23 23:50:52 by nosuzuki         ###   ########.fr       */
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
# define SPEC 0.3
typedef struct s_list	t_list;
typedef struct s_img	t_img;
typedef struct	s_rgb
{
	double		r;
	double		g;
	double		b;
}				t_rgb;
typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
	double		len;
}				t_vect;
typedef struct	s_sp
{
	t_vect		o;
	double		r;
}				t_sp;
typedef struct	s_point
{
	t_vect		normal;
	t_vect		position;
}				t_point;
struct  s_list
{
	void		*obj;
	double		(*f)(void *, t_img);
	t_list		*next;
};
struct  s_img {
    void        *img;
    char        *addr;
	int			w;
	int			h;
    int         bpp;
    int         line_length;
    int         endian;
	void		*mlx;
	void		*win;
	t_point		point;
	t_list		*lst;
	t_rgb		rgb;
	t_sp		sp;
};
//win minus or int_max

void            my_mlx_pixel_put(t_img *data, int x, int y, int color);
int             close2(int keycode, t_img *vars);
int             close1(int keycode, t_img *vars);
double			dot(t_vect v1, t_vect v2);
t_vect			cross(t_vect v1, t_vect v2);
t_vect			vect_add(t_vect v1, t_vect v2);
t_vect			vect_mult(t_vect v1, double d);
t_vect			vect_sub(t_vect v1, t_vect v2);
t_vect			point_to_vect(double x, double y, t_img img);
t_vect			vect_init(double x, double y, double z);
double			sphere(t_vect cam, t_vect ray, t_vect sp, double r, void *obj);
t_vect			vect_unit(t_vect v);
int				light(t_vect point, t_vect sp, t_vect u_view);
int				spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl);



#endif