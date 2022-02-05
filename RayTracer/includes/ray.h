//
// Created by Achiote Tory on 1/21/22.
//

#ifndef RAY_H
#define RAY_H

#include "minirt.h"

typedef struct s_ray	t_ray;
typedef struct s_view	t_view;
typedef struct s_scene_attributes	t_scene;

struct s_ray
{
	t_point 	origin;
	t_vector 	direction;
	double 		dot_direction;
};

t_ray		new_ray(t_point *origin, t_vector *direction);
t_point		ray_position(t_ray *ray, double distance);
t_ray		transform(t_ray *ray, t_matrix *matrix);
t_ray		trace_ray(t_point *origin, int x, int y, t_view *view);

#endif
