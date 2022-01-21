//
// Created by Achiote Tory on 1/21/22.
//

#include "ray.h"


t_ray	new_ray(t_point *origin, t_vector *direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_point	ray_position(t_ray *ray, double distance)
{
	t_tuple tmp;

	tmp = multiply_on_scalar(ray->direction, distance);
	return (add(ray->origin, &tmp));
}
