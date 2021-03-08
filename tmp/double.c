#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <unistd.h>

typedef union d
{
	double d;
	uint64_t u;
}		t_bit;

void putnbr(uint64_t n)
{
	if (n > 2)
		putnbr(n /2);
	write(1, &"01"[n % 2], 1);
}

int main()
{
	// t_bit d;
	// double dd;
	// dd = 0;
	// d.d = DBL_MAX;
	// // if (d.u & (uint64_t)0x7ff << 52)
	// // 	printf("%d\n", 1);
	// // putnbr(d.u);
	// // puts("");
	// // putnbr((uint64_t)0x7ff << 52);
	// // puts("");
	// // uint64_t i = d.d;
	// printf("%f\n", DBL_MAX);
	// printf("%ld\n", d.u);
	// // printf("%ld\n", i);
	printf("%d", 3 % 3);
}