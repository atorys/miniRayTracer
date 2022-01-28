//
// Created by Achiote Tory on 1/22/22.
//

#include "minirt.h"

void apply_light(t_scene *scene, t_light *light, t_color *color, t_ray *ray, double distance, t_vector * normal)
{
	t_vector light_ray;
	t_vector minus_d;
	t_point point;

	t_color diffuse;
	t_color specular;

	t_color effective_color;

	point = ray_position(ray, distance);
	light_ray = subtract(&(light->center), &point);
	normalize(&light_ray);

	effective_color = ft_color_multiplication(&light->color, light->bright);
	minus_d = multiply_on_scalar(ray->direction, -1);\
	if (dot(&light_ray, normal) < 0)
	{
		diffuse = new_tuple(0, 0, 0, COLOR);
		specular = new_tuple(0, 0 ,0, COLOR);
	}
	else
	{
		diffuse = multiply_on_scalar(&effective_color, dot(&light_ray, normal));
		t_vector minus_light = multiply_on_scalar(&light_ray, -1);
		t_vector reflected = reflect(&minus_light, normal);
		if (dot(&reflected, &minus_d) <= 0)
			specular = new_tuple(0, 0, 0, COLOR);
		else {
			double factor = ft_pow(dot(&reflected, &minus_d), 140);
			specular = multiply_on_scalar(&light->color, factor * 0.9);
		}
	}
	*color = ft_color_addition(color, &diffuse);
	*color = ft_color_addition(color, &specular);
}

bool	is_shadowed(t_scene *scene, t_light *light, t_point *point)
{
	t_vector	point_light_v;
	double		distance;
	t_ray		ray;
	t_hit		h;

	point_light_v = subtract(&light->center, point);
	distance = module_v(&point_light_v);
	normalize(&point_light_v);
	ray = new_ray(point, &point_light_v);
	h = hit(scene, &ray);
	if (h.object && h.pair.x < distance)
		return (true);
	return (false);
}

t_color	lightning(t_scene *scene, t_object *object, t_ray *ray, double distance)
{
	t_light	*light_ptr;
	t_color	color;
	t_vector normal;
	t_point point;

	color = object->color;
	point = ray_position(ray, distance);
	normal = normal_at(object, &point);
	light_ptr = scene->l_lights;
	t_color ambient = ft_color_multiplication(&scene->a_light.color, scene->a_light.ratio);
	color = ft_color_addition(&color, &ambient);
	while (light_ptr)
	{
//		t_vector n = multiply_on_scalar(&normal, EPSILON);
//		point = add(&point, &n);
		if (!is_shadowed(scene, light_ptr, &point)) {
			apply_light(scene, light_ptr, &color, ray, distance, &normal);
		}
		light_ptr = light_ptr->next;
	}
//	color = ft_color_multiplication(&color, scene->a_light.ratio);
	return (color);
}
