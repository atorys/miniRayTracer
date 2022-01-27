//
// Created by Achiote Tory on 1/21/22.
//

#include "ray.h"


t_ray	new_ray(t_point *origin, t_vector *direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.dot_direction = dot(direction, direction);
	return (ray);
}

t_point	ray_position(const t_ray *ray, double distance)
{
	t_tuple tmp;

	tmp = multiply_on_scalar(ray->direction, distance);
	return (add(ray->origin, &tmp));
}

t_ray	transform(const t_ray *ray, t_matrix *matrix) // todo: не работает
{
	t_ray		new;
	t_point		new_origin;
	t_vector	new_direction;

	new_origin = multiply_matrix_tuple(inverse(matrix), ray->origin);
	new_direction = multiply_matrix_tuple(inverse(matrix), ray->direction);
	new = new_ray(&new_origin, &new_direction);
	return (new);
}
