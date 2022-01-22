//
// Created by Achiote Tory on 1/21/22.
//

#ifndef RAY_H
#define RAY_H

#include "minirt.h"

typedef struct s_ray	t_ray;
typedef struct s_scene_attributes	t_scene;

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

t_ray		new_ray(t_point *origin, t_vector *direction);
t_point		ray_position(const t_ray *ray, double distance);
t_ray		transform(const t_ray *ray, t_matrix *matrix);

t_vector	reflect(const t_vector* ray, const t_vector* normal);
int			lightning(t_scene *scene,
					 t_object *object,
					 t_ray *ray,
					 double distance);

#endif
