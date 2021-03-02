/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/02 02:51:07 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTS_H
# define PUTS_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# define PI 3.14159265
# define GLOSS 8
# define AMB 0.1
// # define AMB 1
// # define DIFF 0.69 * 0.9
# define DIFF 0.9
# define SPEC 0.9
// # define SPEC 0.3
typedef struct s_lst	t_lst;
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
typedef struct s_cam
{
	t_vect		pos;
	int			fov;
}				t_cam;
typedef struct s_light
{
	t_vect		pos;
	t_rgb		rgb;
	double		pow;
}				t_light;
typedef struct	s_sp
{
	t_vect		o;
	double		r;
	t_rgb		rgb;
}				t_sp;
typedef struct	s_sq
{
	t_vect		p;
	t_vect		n;
	t_vect		my;
	t_rgb		rgb;
	double		size;
}				t_sq;
typedef struct	s_pl
{
	t_vect		p;
	t_vect		n;
	t_rgb		rgb;
}				t_pl;
typedef struct	s_cy
{
	t_vect		p;
	t_vect		n;
	double		r;
	double		h;
	t_rgb		rgb;
}				t_cy;
typedef struct	s_tri
{
	t_vect		o;
	t_vect		p;
	t_vect		q;
}				t_tri;
typedef struct	s_node
{
	t_vect		pos;
	t_vect		normal;
	t_rgb		rgb;
	double		pos_len;
}				t_node;
struct  s_lst
{
	void		*obj;
	double		(*f)();
	t_lst		*next;
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
	t_rgb		rgb;
	// t_cam		cam;
	t_light		amb;
	t_light		light;
	t_node		node;
	t_lst		*lst;
	t_lst		*start;
	double		fov;
	t_vect		cam;
	t_vect		cam_normal;
	t_vect		view;
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
double			vect_len(t_vect v);
double			sphere(t_img *img, t_sp *sp);
double			quadratic_formula(double a, double b, double d);
t_vect			vect_unit(t_vect v);
double			light(t_img *img);
double			spec(t_vect u_view, t_vect u_light, t_vect u_normal, double cos_nl);
t_lst			*ft_lstnew_rt(void *obj, void *func);
t_lst			*ft_lstadd_front_rt(t_lst **lst, t_lst *new);
t_rgb			rgb_init(int r, int g, int b);
int				color(t_rgb obj, t_light light, double ref);
int				pl_init(char *data, t_img *img);
int				sp1_init(char *data, t_img *img);
int				sq_init(char *data, t_img *img);
int				cy_init(char *data, t_img *img);
int				tr_init(char *data, t_img *img);
int				parse_resolution(char *start, t_img *img);
int				resolution_init(char *data, t_img *img, int64_t *flag);
int				amb_init(char *data, t_img *img, int64_t *flag);
int				cam_init(char *data, t_img *img, int64_t *flag);
int				light1_init(char *data, t_img *img, int64_t *flag);
int				ft_isspace(int c);
char			*skip_space(char *s);
char			*skip_not_space(char *s);
char			*trim_space(char **s);
int				comma_count(char *s);
int				split_count(char **s);
int				split_comma(char *s, double *a, double *b, double *c);
int				parse_rgb(char *s, double *r, double *g, double *b);
double			ft_mini_atoinf(const char *s, char type);
int				split_comma_normal(char *s, double *a, double *b, double *c);
int				check_range(char *s, char c);
double			plane(t_img *img, t_sp *pl);
double			square(t_img *img, t_sp *sq);
double			cylinder(t_img *img, t_sp *cy);
#endif