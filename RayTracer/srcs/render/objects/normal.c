/****************************************************************************
 *			Функции вычисления вектора нормали фигур :	сферы				*
 *														плоскости			*
 *														цилиндра			*
 ****************************************************************************/
//
// Created by Achiote Tory on 1/22/22.
//

#include "render.h"

/*
 * Общий вызов функции нахождения вектора нормали
 * через внутренний указатель на функцию каждого обЬекта
 */
t_vector	normal_at(t_object* this, void *computations)
{
	return(this->normal_func(this, computations));
}

t_vector	normal_at_sphere(void *this, void *computations)
{
	t_comp		*comp;
	t_sphere	*sphere;
	t_vector	normal;

	sphere = (t_sphere *)this;
	comp = (t_comp *)computations;
	normal = subtract(&(comp->point), &(sphere->object.center));
	normalize(&normal);
	return (normal);
}

t_vector	normal_at_plane(void *this, void *computations)
{
	t_comp		*comp;
	t_plane		*plane;
	t_vector	normal;

	plane = (t_plane *)this;
	comp = (t_comp *)computations;
	if (dot(&(plane->orientation), &(comp->eye_v)) < 0)
		normal = multiply_on_scalar(&(plane->orientation), -1);
	else
		normal = plane->orientation;
	normalize(&normal);
	return (normal);
}

double closest_point_on_cylinder_axis(t_cylinder *cylinder, t_ray *ray, double t1, double t2)
{
	t_vector origin_to_center;
	double m1;
	double m2;

	origin_to_center = subtract(&(ray->origin),
								&(cylinder->object.center));

	m1 = dot(&(ray->direction), &(cylinder->orientation)) * t1;
	m1 += dot(&origin_to_center, &(cylinder->orientation));

	m2 = dot(&(ray->direction), &(cylinder->orientation)) * t2;
	m2 += dot(&origin_to_center, &(cylinder->orientation));

	if (m1 > -cylinder->height/2 && m1 < cylinder->height/2)
	{
		if (m2 > -cylinder->height/2 && m2 < cylinder->height/2 && m1 > m2)
			m1 = m2;
	}
	else if (m2 > -cylinder->height/2 && m2 < cylinder->height/2
	&& m1 < -cylinder->height/2)
		m1 = m2;
	else
		m1 = MAX_DOUBLE;
	return (m1);
}

t_vector	normal_at_cylinder(void *this, void *computations)
{
	t_comp		*comp;
	t_cylinder	*cylinder;
	t_vector	normal;
	t_point 	a;
	double 		closest_distance;

	cylinder = (t_cylinder *)this;
	comp = (t_comp *)computations;

	closest_distance = closest_point_on_cylinder_axis(cylinder, comp->ray,
													comp->t1,
													comp->t2);
	a = multiply_on_scalar(&(cylinder->orientation), closest_distance);
	a = add(&(cylinder->object.center), &a);

	normal = subtract(&(comp->point), &a);
	normalize(&normal);
	return (normal);
}
