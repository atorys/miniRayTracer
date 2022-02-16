//
// Created by Achiote Tory on 1/21/22.
//

#ifndef RAY_H
#define RAY_H

#include "tuple.h"
#include "matrix.h"

typedef struct s_ray	t_ray;

struct s_ray
{
	t_point 	origin;
	t_vector 	direction;
	double 		dot_direction;
};

t_ray		new_ray(t_point *origin, t_vector *direction);
t_point		ray_position(t_ray *ray, double distance);
t_ray		transform(t_ray *ray, t_matrix *matrix);

#endif
