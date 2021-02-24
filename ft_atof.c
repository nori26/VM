#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
// typedef union	u
// {
// 	double		d;
// 	uint64_t	bit;
// }				t_bit;

// double	ft_mini_atof(const char *s)
// {
// 	int		neg;
// 	int		exp;;
// 	t_bit	n;
// 	double	frac;

// 	n.d = 0;
// 	neg = -1;
// 	neg = (*s == '+' || *s == '-') ? *s++ == '-' : -1;
// 	while ('0' <= *s && *s <= '9')
// 		n.d = n.d * 10 + *s++ - '0';
// 	if ((*s && *s != '.') || ((n.bit >> 52) & 0x7ff) == 0x7ff)
// 		return (DBL_MAX);
// 	if (!*s)
// 		return (n.d);
// 	exp = 0;
// 	frac = 0;
// 	while ('0' <= *++s && *s <= '9')
// 		if (frac < DBL_MAX / 20)
// 		{
// 			exp++;
// 			frac = frac * 10 + *s - '0';
// 		}
// 	while (exp-- > 0)
// 		frac /= 10;
// 	return (*s ? DBL_MAX : -neg * (n.d + frac)); 
// }
typedef union	u
{
	double		d;
	uint64_t	bit;
}				t_bit;

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

double	ft_mini_atof(const char *s)
{
	int			neg;
	uint64_t	len;
	t_bit		n;
	double		frac;

	if (*s == '0' && s[1] && s[1] != '.')
		return (DBL_MAX);
	n.d = 0;
	neg = -1;
	neg = (*s == '+' || *s == '-') ? *s++ == '-' : -1;
	while ('0' <= *s && *s <= '9')
		n.d = n.d * 10 + *s++ - '0';
	if ((*s && *s != '.') || ((n.bit >> 52) & 0x7ff) == 0x7ff)
		return (DBL_MAX);
	if (!*s)
		return (n.d);
	frac = 0;
	len = ft_strlen(s);
	while ('0' <= s[--len] && s[len] <= '9')
		frac = frac / 10 + (s[len] - '0') / 10.0;
	return (s[len] == '.' ? -neg * (n.d + frac) : DBL_MAX); 
}

int main()
{
	char *s;
	s = "0";
	double d;
	if (((d = ft_mini_atof(s)) == DBL_MAX))
		puts("err");
	printf("%.1200f\n", d);
	printf("%.1200f\n", atof(s));
}