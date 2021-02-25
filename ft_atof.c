/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosuzuki <nosuzuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:57:47 by nosuzuki          #+#    #+#             */
/*   Updated: 2021/02/25 18:58:13 by nosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

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
	double		frac;
	double		integer;

	if (!s)
		return (INFINITY);
	neg = *s == '-' ? *s++ == '-' : 0;
	if ((*s == '0' && s[1] && s[1] != '.') || !('0' <= *s && *s <= '9'))
		return (INFINITY);
	integer = 0;
	while ('0' <= *s && *s <= '9')
		integer = integer * 10 + *s++ - '0';
	if ((*s && *s != '.') || integer == INFINITY || ((len = ft_strlen(s)) == 1))
		return (INFINITY);
	frac = 0;
	while (*s && '0' <= s[--len] && s[len] <= '9')
		frac = frac / 10 + (s[len] - '0');
	if (len > 0)
		return (INFINITY);
	return (neg ? -(integer + frac / 10) : integer + frac / 10); 
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

// double    ft_mini_atof(char *str)
// {
//     int        sign;
//     double    integer;
//     double    decimal;
//     int        len;

//     sign = 1;
//     integer = 0;
//     decimal = 0;
//     if (str == NULL)
//         return (INFINITY);
//     if (*str == '-')
//         sign *= -1 + (*str++ * 0);
//     if (!ft_isdigit(*str)|| (*str == '0' && str[1] && str[1] != '.'))
//         return (INFINITY);
//     while (ft_isdigit(*str))
//         integer = integer * 10 + (*str++ - '0');
//     if ((*str && *str++ != '.') || integer == INFINITY)
//         return (INFINITY);
//     len = ft_strlen(str);
//     while (len > 0 && ft_isdigit(str[len - 1]))
//         decimal = decimal / 10 + (str[--len] - '0');
//     if (len != 0)
//         return (INFINITY);
//     return (sign * (integer + decimal / 10));
// }
int atof_test(int i, char *s)
{
	double d;

	printf("=========%d=========\n", i);
	if (((d = ft_mini_atof(s)) == INFINITY))
		return (puts("err"));
	printf("%.1500g\n", d);
	printf("%.1500g\n\n", atof(s));
	return (0);
}

int main()
{
	char buf[2000];

	sprintf(buf, "%.1500f", DBL_MIN);
	atof_test(1, buf);
	sprintf(buf, "%.1500f", DBL_MIN / 1000000);
	atof_test(1, buf);
	sprintf(buf, "%.1500f", DBL_MAX);
	atof_test(2, buf);
	atof_test(3, "0");
	atof_test(4, "1");
	atof_test(5, "100");
	atof_test(6, "12345");
	atof_test(7, "1.1");
	atof_test(8, "0.1");
	atof_test(9, "0.01");
	atof_test(10, "-0.01");
	atof_test(11, "-1.01");
	atof_test(12, "-100.01");
	atof_test(13, "-100");

	puts("\n\n=====================================");
	puts("===============error=================");
	puts("=====================================\n");
	atof_test(0, "01");
	atof_test(1, "001");
	atof_test(2, "1.");
	atof_test(3 ,"1..");
	atof_test(4, "0.");
	atof_test(5, "1a");
	atof_test(6, "a1");
	atof_test(7, "1.a");
	atof_test(8, "1.1a");
	atof_test(9, "1.1a1");
	atof_test(10, "1.a.1");
	atof_test(11, "1...1");
	atof_test(12, "1...1.");
	atof_test(13, ".");
	buf[0] = '9';
	atof_test(14, buf);
	atof_test(15, "+100");
	atof_test(16, "-");
	atof_test(17, "+");
	atof_test(18, "...");
	atof_test(19, "00");
	atof_test(20, "0.0");
	atof_test(21, "-0.0");
	atof_test(22, "-0");
	atof_test(23, "-00");
	atof_test(24, "-.");
	atof_test(25, "-.1");
	atof_test(26, "-1.");
	atof_test(27, ".1");
	atof_test(28, ".1a");
	atof_test(29, ".a1");
	atof_test(30, "-a");
	atof_test(31, "+a");
	atof_test(32, "1.1.");
	atof_test(33, "1.1.1");
	atof_test(34, "1-");
	atof_test(35, "--1");
	atof_test(36, "-+1");
	atof_test(37, "+-1");
	atof_test(38, "1..1");
	atof_test(39, "--");
	atof_test(40, "++");
	atof_test(41, "\"");
	atof_test(42, "\'");
	atof_test(43, "..");
	atof_test(44, NULL);
}