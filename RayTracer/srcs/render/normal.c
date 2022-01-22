//
// Created by Achiote Tory on 1/22/22.
//

#include "objects.h"

t_vector	normal_at(t_object* this, t_point *point)
{
	return(this->normal_func(this, point));
}

t_vector	normal_at_sphere(t_sphere *sphere, const t_point *point)
{
	t_vector normal;

	normal = subtract(point, &(sphere->object.center));
	normalize(&normal);
	return (normal);
}
