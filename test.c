#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct s_list t_list;
struct s_vect;
typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
	long long	d;
	void (*f)(t_list);
}				t_vect;
struct			s_list
{
	t_vect		v;
};

t_vect	cross(t_vect v1, t_vect v2)
{
	t_vect ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

char 			g_c = 'a';
double			vect_len(t_vect v)
{
	double		len;

	len = 0;
	v.x = 0;
	return (len);
}
void			test()
{
	printf("%c\n", g_c);
}

void			test2(int a)
{
	printf("%d\n", a);
}
int				main()
{
	void		(**f)();
	t_vect		v;

	f = malloc(30);
	f[0] = test;
	f[1] = test2;
	f[0]();
	f[1](1);
	v.x = 1;
}