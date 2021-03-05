#include <stdio.h>
#include <math.h>

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
	long long		d;
}				t_vect;

t_vect	cross(t_vect v1, t_vect v2)
{
	t_vect ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

char c = 'a';
double			vect_len(t_vect v)
{
	double len;

	len = 0;
	v.x = 0;
	// len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}
void test()
{
	printf("%c\n", c);
}

int main()
{
	test();
}