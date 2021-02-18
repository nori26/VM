#include <stdio.h>

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

t_vec	outer(t_vec v1, t_vec v2)
{
	t_vec ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

int main()
{
	t_vec v1 = {3, 4, 1};
	t_vec v2 = {3, 7, 5};
	t_vec ret = outer(v1, v2);
	
}