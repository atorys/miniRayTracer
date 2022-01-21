#ifndef MATHS_H
# define MATHS_H

# define MAX_DOUBLE	9223372036854
# define EPSILON	0.00001
# define PI			3.14

#include <stdbool.h>

typedef struct s_pair	t_pair;

struct s_pair
{
	double	x;
	double	y;
};

double 	radians(double degrees);
double	ft_max_module(double a, double b);
double	ft_min_module(double a, double b);
double	ft_max(double a, double b);
double	ft_min(double a, double b);
double	ft_pow(double num, int n);
double	ft_module(double a);
bool	ft_equal(double a, double b);
t_pair	ft_quadratic_roots(double a, double b, double c);

#endif
