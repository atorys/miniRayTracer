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
