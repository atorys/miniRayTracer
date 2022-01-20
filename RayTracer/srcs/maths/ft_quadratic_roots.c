#include "maths.h"
#include <math.h>

t_pair	ft_quadratic_roots(double a, double b, double c)
{
	double	d;
	t_pair	point;

	d = (b * b) - (4 * c * a);
	point.x = MAX_DOUBLE;
	point.y = MAX_DOUBLE;
	if (d >= 0)
		point.x = (-b + sqrt(d)) / (2 * a);
	else if (d > 0)
	{
		d = (-b - sqrt(d)) / (2 * a);
		if (point.x > d)
		{
			point.y = point.x;
			point.x = d;
		}
		else
			point.y = (-b - sqrt(d)) / (2 * a);
	}
	return (point);
}

bool	ft_equal(double a, double b)
{
	return (ft_module(a - b) < EPSILON);
}
