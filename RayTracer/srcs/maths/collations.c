#include "maths.h"


bool	ft_equal(double a, double b)
{
	return (ft_module(a - b) < EPSILON);
}

double	ft_max_module(double a, double b)
{
	if (a * (double)(1 - (2 * (a < 0))) > b * (double)(1 - (2 * (b < 0))))
		return (a * (double)(1 - (2 * (a < 0))));
	else
		return (b * (double)(1 - (2 * (b < 0))));
}

double	ft_min_module(double a, double b)
{
	if (a * (double)(1 - (2 * (a < 0))) < b * (double)(1 - (2 * (b < 0))))
		return (a * (double)(1 - (2 * (a < 0))));
	else
		return (b * (double)(1 - (2 * (b < 0))));
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_module(double a)
{
	if (a < 0)
		return (-1 * a);
	return (a);
}
