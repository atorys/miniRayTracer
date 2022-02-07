#include "objects.h"
#include "ray.h"

t_pair	intersect(t_object*	this, void *ray)
{
	return (this->intersection_func(this, ray));
}

t_pair	intersect_sp(void *this, void *ray)
{
	t_vector	sphere_to_ray;
	t_sphere	*sphere;
	t_ray 		*r;
	double		a;
	double		b;
	double		c;

	sphere = (t_sphere *)this;
	r = (t_ray *)ray;
	sphere_to_ray = subtract(&(r->origin), &(sphere->object.center));
	a = r->dot_direction;
	b = 2 * dot(&(r->direction), &sphere_to_ray);
	c = dot(&sphere_to_ray, &sphere_to_ray) - (sphere->squared_radius);
	return (ft_quadratic_roots(a, b, c));
}

t_pair	intersect_pl(void *this, void *ray)
{
	t_plane		*plane;
	t_ray 		*r;
	t_pair 		pair;
	t_vector	plane_to_ray;
	double		a;
	double		b;

	plane = (t_plane *)this;
	r = (t_ray *)ray;

	pair.x = MAX_DOUBLE;
	pair.y = MAX_DOUBLE;

	plane_to_ray = subtract(&(r->origin), &(plane->object.center));
	b = dot(&(plane->orientation), &(r->direction));
	if (b < 0) {
		plane->orientation = multiply_on_scalar(&(plane->orientation), -1);
		b = dot(&(plane->orientation), &(r->direction));
	}
	a = dot(&(plane->orientation), &plane_to_ray);
	if (b != 0 && ((a > 0 && b < 0) || (a < 0 && b > 0)))
		pair.x = -a / b;
	return (pair);
}

t_pair	intersect_cy(void *this, void *ray)
{
	t_cylinder	*cylinder;
	t_vector	cylinder_to_ray;
	t_ray 		*r;
	double		a;
	double		b;
	double		c;

	cylinder = (t_cylinder *)this;
	r = (t_ray *)ray;

	cylinder_to_ray = subtract(&(r->origin), &(cylinder->object.center));
	a = r->dot_direction - ft_pow(dot(&(r->direction), &(cylinder->orientation)), 2);
	b = 2 * (dot(&(r->direction), &cylinder_to_ray)) - dot(&(r->direction), &(cylinder->orientation)) *
														dot(&cylinder_to_ray, &(cylinder->orientation));
	c = dot(&cylinder_to_ray, &cylinder_to_ray) - ft_pow(dot(&cylinder_to_ray, &(cylinder->orientation)), 2)
												-	ft_pow(cylinder->diameter/2, 2);
	return (ft_quadratic_roots(a, b, c));
}