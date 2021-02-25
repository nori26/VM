/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:07:00 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/23 23:31:28 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "puts.h"

typedef struct s_list t_list;
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
typedef struct  s_img {
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
}               t_img;
#endif