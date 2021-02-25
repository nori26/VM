#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>

void			test2(double a)
{
	if (a == -INFINITY)
		printf("%f\n", a);
}
int				main()
{
	// test2(DBL_MAX * -1.000000000001);
	// test2(DBL_MAX * -3);
	// test2(DBL_MAX * -1.1);
	// test2(DBL_MAX * -1.15);
	// test2(DBL_MAX);
	// test2(DBL_MAX);
	// test2(DBL_MAX);
	// test2(DBL_MAX);
	// test2(DBL_MAX);
	// test2(DBL_MAX);
	char *s = malloc(1);
}