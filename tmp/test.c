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

typedef struct sss
{
	char c;
	short i;
} sss;
typedef struct ss
{
	char i;
	char j;
} ss;
#include <stdint.h>
#include <stdio.h>

int  god(uintmax_t u, char *num, uintmax_t base, int len)
{
    if (u >= base)
        len = god(u / base, num, base, len);
    num[len++] = "0123456789abcdef"[u % base];
    return (len);
}

int ft_itoa_god(intmax_t n, char *num, int base)
{
    int       len;
    uintmax_t u;

    u = n >= 0 ? n : -n;
    len = god(u, num, base, 0);
    num[len] = '\0';
	return (len);
}

void putnbr(__uint128_t n)
{
    if (n > 9)
        putnbr(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

// int main()
// {
//     // char num[30];
//     __uint128_t t = 9223372036854775807;
//     long double ld;
//     double d;

//     ld = LDBL_MAX;
//     d = DBL_MAX;
//     d *= 100;
//     printf("%Lf\n\n", ld);
//     printf("%f\n", d);
//     t = t * 2 + 100;
//     // printf("%zu\n", SIZE_MAX);
//     // putnbr(t);
//     // ft_itoa_god(INT_MAX, num, 10);
//     // printf("%s\n", num);
// }

void			test()
{
	static char *c;

	c = malloc(1);
}

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
	printf("%d\n", (int)INFINITY);
	printf("%d\n", (int)INFINITY);
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
	fd = open("a.txt", O_RDONLY);
	fd = read(fd, NULL, 5);
	d = INFINITY;
	if (d > 1)
		printf("aaa%d\n", fd);
	char *a;
	a = malloc(1);
	test();
	printf("%zu\n%zu\n", sizeof(ss), sizeof(sss));
}
