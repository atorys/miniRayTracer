//
// Created by Achiote Tory on 1/21/22.
//

#ifndef RAY_H
#define RAY_H

#include "minirt.h"

typedef struct s_ray	t_ray;

struct s_ray
{
	t_point 	*origin;
	t_vector 	*direction;
};

//struct s_intersection
//{
//	t_pair		t;
//	t_object*	object;
//};

t_ray	new_ray(t_point *origin, t_vector *direction);
t_point	ray_position(t_ray *ray, double distance);


t_pair	intersect(t_object*	this, void *ray);
t_pair	intersect_sp(void *this, void *ray);

#endif
