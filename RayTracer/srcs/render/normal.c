//
// Created by Achiote Tory on 1/22/22.
//

#include "objects.h"
#include "minirt.h"

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
	t_plane *plane;
	t_vector normal;

	plane = (t_plane *)this;
	(void)computations;
	normal = plane->orientation;
	normalize(&normal);
	return (normal);
}

double closest_point_on_cylinder_axis(t_cylinder *cylinder, t_ray *ray, double t1, double t2)
{
	t_vector ray_origin_to_cylinder_center;
	double m1;
	double m2;

	ray_origin_to_cylinder_center = subtract(&(ray->origin), &(cylinder->object.center));

	m1 = dot(&(ray->direction), &(cylinder->orientation)) * t1;
	m1 += dot(&ray_origin_to_cylinder_center, &(cylinder->orientation));

	m2 = dot(&(ray->direction), &(cylinder->orientation)) * t2;
	m2 += dot(&ray_origin_to_cylinder_center, &(cylinder->orientation));

	if (m1 > 0 && m1 < cylinder->height)
	{
		if (m2 > 0 && m2 < cylinder->height && m1 > m2)
			m1 = m2;
	}
	else if (m2 > 0 && m2 < cylinder->height && m1 < 0)
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
	cylinder = (t_cylinder *)this;
	comp = (t_comp *)computations;

	comp->m_param1 = closest_point_on_cylinder_axis(cylinder, comp->ray, comp->t1, comp->t2);
	a = multiply_on_scalar(&(cylinder->orientation), comp->m_param1);
	a = add(&(cylinder->object.center), &a);

	normal = subtract(&(cylinder->object.center), &a);
	normal = subtract(&(comp->point), &a);
	normalize(&normal);
	return (normal);
}
