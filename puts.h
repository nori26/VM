/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:19:18 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/03/16 08:29:50 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTS_H
# define PUTS_H
# include <stdio.h>
# include <string.h>
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# define PI 3.14159265
# define BMP_MAX 3000
# define GLOSS 30
# define EPSILON img->node.dist / PREC
# define PREC 10000000000000
# define ON  1
# define OFF 0
# define DIFF 0.9
# define SPEC 0.9
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

typedef struct s_idlst	t_idlst;
typedef struct s_clist	t_clist;
typedef struct s_llist	t_llist;
typedef struct s_pic	t_pic;
enum			e_id
{
				SP,
				PL,
				SQ,
				CY,
				TR,
				CAM,
				LIGHT,
				AMB,
				RES,
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
	t_vect		n;
	t_vect		to_cam;
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
	t_vect		to_cam;
}				t_sq;
typedef struct	s_pl
{
	t_rgb		rgb;
	t_vect		p;
	t_vect		n;
	t_vect		to_cam;
}				t_pl;
typedef struct	s_cy
{
	t_rgb		rgb;
	t_vect		p;
	t_vect		n;
	t_vect		node_n;
	double		r;
	double		h;
	t_vect		to_cam;
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
	t_vect		to_cam;
}				t_tr;
typedef struct	s_node
{
	t_rgb		rgb;
	t_vect		pos;
	t_vect		normal;
	double		dist;
}				t_node;
struct			s_idlst
{
	int			id;
	void		*obj;
	t_idlst		*next;
};
struct			s_clist
{
	t_vect		pos;
	t_vect		n;
	double		fov;
    void		*img;
    char        *adr;
	t_vect		cent;
	t_clist		*next;
	t_clist		*prev;
};
typedef struct s_llist
{
	t_vect		pos;
	t_rgb		rgb;
	int			on;
	double		pow;
	t_llist		*next;
}				t_llist;
// struct  		s_pic
// {
//     void        *img;
// 	int			bmp;
// 	int			w;
// 	int			h;
//     int         bpp;
//     int         width_bytes;
//     int         endian;
// 	void		*mlx;
// 	void		*win;
// 	t_vect		ray_start;
// 	t_rgb		rgb;
// 	t_llist		*amb;
// 	t_node		node;
// 	t_idlst		*lst;
// 	t_clist		*cam;
// 	t_llist		*light;
// 	t_idlst		*o_start;
// 	t_clist		*c_start;
// 	t_llist		*l_start;
// 	double		fov;
// 	t_vect		cam_normal;
// 	t_vect		u_view;
// 	t_vect		v_view;
// 	double		(*f_node_judge[5])();
// 	void		(*f_update_node[5])();
// 	void		(*f_to_cam_vect[5])();
// 	t_vect		(*f_ret_to_cam[5])();
// 	t_vect		(*f_ret_to_raystart[5])();
// 	int			bmp_w;
// 	int			bmp_h;
// 	int			shad;
// };

// void            pixel_put(t_pic *data, int x, int y, int color);
// int             close1(t_pic *vars);
// int             close2(int keycode, t_pic *vars);
// double			dot(t_vect v1, t_vect v2);
// t_vect			cross(t_vect v1, t_vect v2);
// t_vect			vect_add(t_vect v1, t_vect v2);
// t_vect			vect_mult(t_vect v1, double d);
// t_vect			vect_sub(t_vect v1, t_vect v2);
// t_vect			point_to_vect(double x, double y, t_pic img);
// t_vect			vect_init(double x, double y, double z);
// double			vect_len(t_vect v);
// double			quadratic_formula(double a, double b, double c, double *ans);
// t_vect			vect_unit(t_vect v);
// double			light_diff(t_pic *img);
// t_idlst			*ft_lstadd_front_o(t_idlst **lst, t_idlst *new);
// t_clist			*ft_lstadd_front_c(t_clist **lst, t_clist *new);
// t_llist			*ft_lstadd_front_l(t_llist **lst, t_llist *new);
// t_idlst			*ft_lstnew_o(void *obj, void *func);
// t_clist			*ft_lstnew_c(t_clist c);
// t_llist			*ft_lstnew_l(t_llist l);
// t_rgb			rgb_init(int r, int g, int b);
// int				color(t_pic *img);
// void			read_rt(t_pic *img, char *path);
// int				pl_init(char *data, t_pic *img);
// int				sp1_init(char *data, t_pic *img);
// int				sq_init(char *data, t_pic *img);
// int				cy_init(char *data, t_pic *img);
// int				tr_init(char *data, t_pic *img);
// int				parse_resolution(char *start, t_pic *img);
// int				resolution_init(char *data, t_pic *img, int64_t *flag);
// int				amb_init(char *data, t_pic *img, int64_t *flag);
// int				cam_init(char *data, t_pic *img);
// int				light1_init(char *data, t_pic *img);
// int				ft_isspace(int c);
// char			*skip_space(char *s);
// char			*skip_not_space(char *s);
// char			*trim_space(char **s);
// int				comma_count(char *s);
// int				split_count(char **s);
// int				split_comma(char *s, double *a, double *b, double *c);
// int				parse_rgb(char *s, double *r, double *g, double *b);
// double			ft_mini_atoinf(const char *s, char type);
// int				split_comma_normal(char *s, double *a, double *b, double *c);
// int				check_range(char *s, char c);
// double			sphere(t_pic *img, t_sp *sp, t_vect u_view, t_vect to_raystart);
// double			plane(t_pic *img, t_pl *pl, t_vect u_view, t_vect to_raystart);
// double			square(t_pic *img, t_sq *sq, t_vect u_view, t_vect to_raystart);
// double			cylinder(t_pic *img, t_cy *cy, t_vect u_view,
// 				t_vect to_raystart);
// double			triangle(t_pic *img, t_tr *tr, t_vect u_view,
// 				t_vect to_raystart);
// int				check_parallel(t_vect a, t_vect b, t_vect c);
// void			vprint(t_vect v);
// int				is_inside(t_tr tr, t_vect node);
// double			primary_colors(t_pic *img, double diff, double spec, char rgb);
// void			func_ary_init(t_pic *img);
// t_idlst			*ft_lstnew_id(void *obj, int id);
// void			update_node(t_pic *img, double dist, t_rgb rgb, t_vect n);
// void			update_node_sp(t_pic *img, double dist, t_sp *sp);
// void			update_node_pl(t_pic *img, double dist, t_pl *pl);
// void			update_node_sq(t_pic *img, double dist, t_sq *sq);
// void			update_node_cy(t_pic *img, double dist, t_cy *cy);
// void			update_node_tr(t_pic *img, double dist, t_tr *tr);
// void			to_cam_vect_sp(t_pic *img, t_sp *sp);
// void			to_cam_vect_pl(t_pic *img, t_pl *pl);
// void			to_cam_vect_sq(t_pic *img, t_sq *sq);
// void			to_cam_vect_cy(t_pic *img, t_cy *cy);
// void			to_cam_vect_tr(t_pic *img, t_tr *tr);
// double			dist_to_plane
// 				(double *vndot, t_vect u_view, t_vect to_cam, t_vect n);
// t_vect			ret_to_cam_sp(t_sp *sp);
// t_vect			ret_to_cam_pl(t_pl *pl);
// t_vect			ret_to_cam_sq(t_sq *sq);
// t_vect			ret_to_cam_cy(t_cy *cy);
// t_vect			ret_to_cam_tr(t_tr *tr);
// t_vect			ret_to_raystart_sp(t_sp *sp, t_vect ray_start);
// t_vect			ret_to_raystart_pl(t_pl *pl, t_vect ray_start);
// t_vect			ret_to_raystart_sq(t_sq *sq, t_vect ray_start);
// t_vect			ret_to_raystart_cy(t_cy *cy, t_vect ray_start);
// t_vect			ret_to_raystart_tr(t_tr *tr, t_vect ray_start);
// t_idlst			*ft_lstnew_id(void *obj, int id);
// t_clist			*ft_lstnew_c(t_clist c);
// t_llist			*ft_lstnew_l(t_llist l);
// t_idlst			*ft_lstadd_front_o(t_idlst **lst, t_idlst *new);
// t_clist			*ft_lstadd_front_c(t_clist **lst, t_clist *new);
// t_llist			*ft_lstadd_front_l(t_llist **lst, t_llist *new);
// void			vect_init_unit_view(t_pic *img, int x, int y);
// void			vect_init_cam_to_screen_center(t_pic *img);
// double			shadow_node_dist(t_pic *img, t_vect u_ray);
// void			shadow(t_pic *img);
// void			node_judge(t_pic *img);
// void			vect_init_object_to_cam(t_pic *img);
// void			light_on(t_pic *img);
// void			make_img(t_pic *img);
// void			ray_trace(t_pic *img);
// int				main_loop(t_pic *img);
// void			draw_img(t_pic *img);
// void			bmp(t_pic *img);
// void			file_header(t_pic *img, int fd);
// void			info_header(t_pic *img, int fd);
// void			image_data(t_pic *img, int fd);
// void			err_exit(t_pic *img, int num);
// char			*err_message(int num);
// void			*lst_free(void *lst, void *next, void *content);
// void			close_img(t_pic *img);
#endif
