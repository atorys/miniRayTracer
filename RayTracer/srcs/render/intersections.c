#include "objects.h"
#include "ray.h"

t_pair	intersect_sp(void *this, void *ray)
{
	t_vector	sphere_to_ray;
	double		a;
	double		b;
	double		c;

	t_sphere *s = (t_sphere *)this;
	t_ray	*r = (t_ray *)ray;
	sphere_to_ray = subtract(r->origin, &(s->object.center));
	a = dot(r->direction, r->direction);
	b = 2 * dot(r->direction, &sphere_to_ray);
	c = dot(&sphere_to_ray, &sphere_to_ray) - ((s->diameter / 2) * (s->diameter / 2));
	return (ft_quadratic_roots(a, b, c));
}

t_pair	intersect(t_object*	this, void *ray)
{
	return (this->intersection_func(this, ray));
}
