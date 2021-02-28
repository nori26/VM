#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

typedef union u
{
	double dbl;
	uint64_t llu;

}t_bit;

int				main()
{
	float f = INFINITY;
	float g = (int)INFINITY;
	double d = INFINITY;
	double e = (int)INFINITY;
	int i = (int)f;
	int j = (int)d;
	int k = (int)INFINITY;
	int64_t l = (int)INFINITY;
	uint64_t m = (int)INFINITY;
	double h = (int)d;

	printf("%f\n", h);
	printf("%ld\n", l);
	printf("%lu\n", m);
	printf("%ld\n", (int)INFINITY);
	printf("%lu\n", (int)INFINITY);
	printf("%f\n", f);
	printf("%f\n", d); 
	printf("%d\n", (int)f); 
	printf("%d\n", (int)d); 
	printf("%f\n", e);
	printf("%.1500g\n", e);
	printf("%f\n", g);
	printf("%.1500g\n", g);
	printf("%d\n", (int)INFINITY);
	printf("INFINITY : %d\n", (int)INFINITY);
	printf("%s%d\n\n", "INFINITY : ", (int)INFINITY);
	printf("%d\n", i);
	printf("%d\n", j); 
	printf("%d\n\n", k);
	printf("%-8s : %f\n", "float", f); 
	printf("%-8s : %f\n", "double", d); 
	printf("%-8s : %d\n", "(int)f", (int)f); 
	printf("%-8s : %d\n", "(int)d", (int)d); 
	printf("%-8s : %d\n\n", "(int)INF", (int)INFINITY);
	printf("%-8s : %d\n", "i", i);
	printf("%-8s : %d\n", "j", j); 
	printf("%-8s : %d\n\n", "k", k);
	int fd;
	char buf[10];
	fd = open("a.txt", O_RDONLY);
	fd = read(fd, buf, 5);
	buf[fd] 
}
