//
// Created by atory on 17.02.2022.
//

#include "render.h"

t_hit	new_hit(t_scene *scene, t_ray *ray)
{
	t_hit		h;
	t_object	*object;
	double		min_distance;

	object = scene->object;
	min_distance = MAX_DOUBLE;
	h.object = NULL;
	while (object)
	{
		t_pair pair = intersect(object, ray);
		if (pair.x < min_distance && pair.x != MAX_DOUBLE && pair.x >= 0) {
			min_distance = pair.x;
			h.object = object;
			h.pair = pair;
		}
		object = object->next;
	}
	return (h);
}

void	prepare_computations(t_comp *computations, t_scene *scene, t_ray *ray)
{
	t_hit	hit;

	hit = new_hit(scene, ray);
	if (!hit.object)
	{
		computations->object = NULL;
		return ;
	}
	computations->ray = ray;
	computations->object = hit.object;
	computations->t1 = hit.pair.x;
	computations->t2 = hit.pair.y;
	computations->point = ray_position(ray, computations->t1);
	computations->eye_v = multiply_on_scalar(&(ray->direction), -1);
	computations->normal = normal_at(computations->object, computations);

	if (dot(&computations->normal, &computations->eye_v) < 0)
		computations->normal = multiply_on_scalar(&(computations->normal), -1);

	computations->reflect_v = reflect(&(ray->direction), &(computations->normal));
	normalize(&(computations->reflect_v));
	computations->over_point = multiply_on_scalar(&(computations->normal), EPSILON);
	computations->over_point = add(&(computations->point), &(computations->over_point));
}
