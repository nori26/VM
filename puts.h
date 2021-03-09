/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/09 07:00:51 by nosuzuki         ###   ########.fr       */
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
# define BMP_MAX 3000
# define AMB 0.1
# define GLOSS 30
# define EPSILON 1.0 / 512
// # define AMB 1
// # define DIFF 0.69 * 0.9
# define DIFF 0.9
// # define SPEC 0.9
# define SPEC 0.9
typedef struct s_idlst	t_idlst;
typedef struct s_clist	t_clist;
typedef struct s_llist	t_llist;
typedef struct s_img	t_img;
enum			e_id
{
				SP,
				PL,
				SQ,
				CY,
				TR,
				CAM,
				LIGHT,
};
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
}				t_vect;

typedef struct	s_sp
{
	t_rgb		rgb;
	t_vect		o;
	double		r;
}				t_sp;
typedef struct	s_sq
{
	t_rgb		rgb;
	t_vect		p;
	t_vect		n;
	t_vect		u_x;
	t_vect		u_y;
	double		size;
}				t_sq;
typedef struct	s_pl
{
	t_rgb		rgb;
	t_vect		p;
	t_vect		n;
}				t_pl;
typedef struct	s_cy
{
	t_rgb		rgb;
	t_vect		p;
	t_vect		n;
	double		r;
	double		h;
}				t_cy;
typedef struct	s_tr
{
	t_rgb		rgb;
	t_vect		a;
	t_vect		b;
	t_vect		c;
	t_vect		ab;
	t_vect		bc;
	t_vect		ca;
	t_vect		ap;
	t_vect		bp;
	t_vect		cp;
	t_vect		n;
	t_vect		cross_a;
	t_vect		cross_b;
	t_vect		cross_c;
}				t_tr;
typedef struct	s_node
{
	t_rgb		rgb;
	t_vect		pos;
	t_vect		normal;
	double		dist;
}				t_node;
typedef union   u_union
{
    t_sp    	sp;
	t_pl		pl;
	t_sq		sq;
	t_cy		cy;
    t_tr    	tr;
	t_rgb		rgb;
}				t_union;
struct			s_idlst
{
	int			id;
	t_union		*type;
	void		*obj;
	double		(*f)();
	t_idlst		*next;
};
struct			s_clist
{
	t_vect		pos;
	t_vect		n;
	double		fov;
    char        *addr;
	t_vect		cent;
	t_clist		*next;
};
typedef struct s_llist
{
	t_vect		pos;
	t_rgb		rgb;
	double		pow;
	t_llist		*next;
}				t_llist;
struct  		s_img
{
    void        *img;
	int			bmp;
	int			w;
	int			h;
    int         bpp;
    int         line_length;
    int         endian;
	void		*mlx;
	void		*win;
	t_rgb		rgb;
	t_llist		*amb;
	t_node		node;
	t_idlst		*lst;
	t_clist		*cam;
	t_llist		*light;
	t_idlst		*o_start;
	t_clist		*c_start;
	t_llist		*l_start;
	double		fov;
	t_vect		cam_normal;
	t_vect		u_view;
	t_vect		v_view;
	double		(*f[5])();
	int			bmp_w;
	int			bmp_h;
};
//win minus or int_max

void            pixel_put(t_img *data, int x, int y, int color);
int             close1(t_img *vars);
int             close2(int keycode, t_img *vars);
double			dot(t_vect v1, t_vect v2);
t_vect			cross(t_vect v1, t_vect v2);
t_vect			vect_add(t_vect v1, t_vect v2);
t_vect			vect_mult(t_vect v1, double d);
t_vect			vect_sub(t_vect v1, t_vect v2);
t_vect			point_to_vect(double x, double y, t_img img);
t_vect			vect_init(double x, double y, double z);
double			vect_len(t_vect v);
double			sphere(t_img *img, t_union *type);
double			quadratic_formula(double a, double b, double d);
double			quadratic_formularge(double a, double b, double c);
t_vect			vect_unit(t_vect v);
double			light_diff(t_img *img);
t_idlst			*ft_lstadd_front_o(t_idlst **lst, t_idlst *new);
t_clist			*ft_lstadd_front_c(t_clist **lst, t_clist *new);
t_llist			*ft_lstadd_front_l(t_llist **lst, t_llist *new);
t_idlst			*ft_lstnew_o(void *obj, void *func);
t_clist			*ft_lstnew_c(t_clist c);
t_llist			*ft_lstnew_l(t_llist l);
t_rgb			rgb_init(int r, int g, int b);
int				color(t_img *img);
void			read_rt(t_img *img, char *path);
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
double			plane(t_img *img, t_pl *pl);
double			square(t_img *img, t_sq *sq);
double			cylinder(t_img *img, t_cy *cy);
double			triangle(t_img *img, t_tr *tr);
int				check_parallel(t_vect a, t_vect b, t_vect c);
int				update_node(t_img *img, double dist, t_rgb rgb);
void			vprint(t_vect v);
int				is_inside(t_tr tr, t_vect node);
double			primary_colors(t_img *img, double diff, double spec, char rgb);
void			func_ary_init(t_img *img);
t_idlst			*ft_lstnew_id(t_union type, int id);
#endif