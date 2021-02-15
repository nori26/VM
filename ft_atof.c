#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <limits.h>

typedef union	u
{
	double		d;
	uint64_t	bit;
}				t_bit;

double	ft_mini_atof(const char *s)
{
	int		neg;
	int		exp;;
	t_bit	n;
	double	frac;

	n.d = 0;
	neg = -1;
	neg = (*s == '+' || *s == '-') ? *s++ == '-' : -1;
	while ('0' <= *s && *s <= '9')
		n.d = n.d * 10 + *s++ - '0';
	if ((*s && *s != '.') || n.bit & (uint64_t)0x7ff << 52)
		return (DBL_MAX);
	if (!*s)
		return (n.d);
	exp = 0;
	frac = 0;
	while ('0' <= *++s && *s <= '9')
		if (frac < DBL_MAX / 20)
		{
			exp++;
			frac = frac * 10 + *s - '0';
		}
	while (exp-- > 0)
		frac /= 10;
	return (*s ? DBL_MAX : -neg * (n.d + frac)); 
}

int main()
{
	char *s;
	s = "0a";
	double d;
	if ((d = ft_mini_atof(s) == DBL_MAX))
		return (puts("err"));
	printf("%.1000f", d);
}