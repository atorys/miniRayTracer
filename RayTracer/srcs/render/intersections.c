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
	sphere_to_ray = subtract(r->origin, &(sphere->object.center));
	a = r->dot_direction;
	b = 2 * dot(r->direction, &sphere_to_ray);
	c = dot(&sphere_to_ray, &sphere_to_ray) - (sphere->squared_radius);
	return (ft_quadratic_roots(a, b, c));
}
