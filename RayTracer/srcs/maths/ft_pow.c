#include "maths.h"

double	ft_pow(double num, int n)
{
	double	num_n;

	num_n = 1;
	while (n > 0 && n--)
		num_n *= num;
	while (n < 0 && n++)
		num_n /= num;
	return (num_n);
}
