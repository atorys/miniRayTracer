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
	{
		point.x = (-b + sqrt(d)) / (2 * a);
		point.y = (-b - sqrt(d)) / (2 * a);
		if (point.x > point.y && point.x >= 0 && point.y >= 0)
		{
			d = point.x;
			point.x = point.y;
			point.y = d;
		}
	}
	return (point);
}
