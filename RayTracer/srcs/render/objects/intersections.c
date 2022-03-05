/****************************************************************************
 *		Функции вычисления пересечения луча с фигурами :	сферой			*
 *															плоскостью		*
 *															цилиндром		*
 ****************************************************************************/

#include "render.h"

/*
 * Общий вызов функции нахождения пересечения
 * через внутренний указатель на функцию каждого обЬекта
 */
t_pair	intersect(t_object*	this, void *ray)
{
	return (this->intersection_func(this, ray));
}

t_pair	intersect_sp(void *this, void *ray)
{
	t_vector	origin_to_center;
	t_sphere	*sphere;
	t_ray 		*r;

	sphere = (t_sphere *)this;
	r = (t_ray *)ray;
	origin_to_center = subtract(&(r->origin), &(sphere->object.center));

	return (ft_quadratic_roots(
								r->dot_direction,
								2 * dot(&(r->direction), &origin_to_center),
								dot(&origin_to_center, &origin_to_center) - sphere->squared_radius));
}

t_pair	intersect_pl(void *this, void *ray)
{
	t_plane		*plane;
	t_ray 		*r;
	t_vector	origin_to_center;
	t_vector	orientation;
	double		a;
	double		b;

	plane = (t_plane *)this;
	r = (t_ray *)ray;

	origin_to_center = subtract(&(r->origin), &(plane->object.center));
	orientation = plane->orientation;
	b = dot(&(orientation), &(r->direction));
	if (b < 0)
	{
		orientation = multiply_on_scalar(&(plane->orientation), -1);
		b = dot(&(orientation), &(r->direction));
	}
	a = dot(&(orientation), &origin_to_center);
	if (b != 0 && ((a > 0 && b < 0) || (a < 0 && b > 0)))
		return ((t_pair){-a/b, MAX_DOUBLE});
	return ((t_pair){MAX_DOUBLE, MAX_DOUBLE});
}

t_pair	intersect_cy(void *this, void *ray)
{
	t_cylinder	*cylinder;
	t_ray 		*r;
	t_pair		roots;
	t_vector 	origin_to_center;

	cylinder = (t_cylinder *)this;
	r = (t_ray *)ray;

	origin_to_center = subtract(&(r->origin), &(cylinder->object.center));
	roots = ft_quadratic_roots(
								(r->dot_direction - ft_pow(dot(&(r->direction),&(cylinder->orientation)), 2)),
								(2 *(dot(&(r->direction), &origin_to_center)
										- dot(&(r->direction),	&(cylinder->orientation))
										* dot(&origin_to_center, &(cylinder->orientation)))),
								(dot(&origin_to_center, &origin_to_center)
										- ft_pow(dot(&origin_to_center, &(cylinder->orientation)), 2)
										- cylinder->squared_radius));
	if (roots.x == MAX_DOUBLE)
		return (roots);
	if (closest_point_on_cylinder_axis(cylinder, ray, roots.x, roots.y) == MAX_DOUBLE)
		roots.x = MAX_DOUBLE;
	return (roots);
}