#include <stdio.h>
#include <math.h>

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vect;

t_vect	cross(t_vect v1, t_vect v2)
{
	t_vect ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

double			vect_len(t_vect v)
{
	double len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}

int main()
{
	t_vect v1 = {1, 1.7320508, 0};
	// t_vec v2 = {3, 7, 5};
	// t_vec ret = outer(v1, v2);

	printf("%f", vect_len(v1));	
}