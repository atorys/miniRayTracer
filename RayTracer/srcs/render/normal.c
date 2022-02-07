//
// Created by Achiote Tory on 1/22/22.
//

#include "objects.h"

t_vector	normal_at(t_object* this, void *point)
{
	return(this->normal_func(this, point));
}

t_vector	normal_at_sphere(void *this, void *point)
{
	t_vector normal;
	t_sphere *sphere;

	sphere = (t_sphere *)this;
	normal = subtract(point, &(sphere->object.center));
	normalize(&normal);
	return (normal);
}

t_vector	normal_at_plane(void *this, void *point)
{
	t_vector normal;
	t_plane *plane;

	plane = (t_plane *)this;
	(void)point;
	normal = plane->orientation;
	normalize(&normal);
	return (normal);
}

t_vector	normal_at_cylinder(void *this, void *point)
{
	t_vector	normal;
	t_vector	orientation;
	t_cylinder	*cylinder;
	double 		m;

	cylinder= (t_cylinder *)this;

	m = dot();

	normal = subtract(point, &(cylinder->object.center));
	orientation = multiply_on_scalar(&(cylinder->orientation), cylinder->height);
	normal = subtract(&normal, &orientation);
	normalize(&normal);
	return (normal);
}
