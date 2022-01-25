//
// Created by Achiote Tory on 1/22/22.
//

#include "minirt.h"


t_vector	reflect(const t_vector* ray, const t_vector* normal)
{
	t_vector reflected;

	t_vector mult = multiply_on_scalar(normal, 2 * dot(ray, normal));
	reflected = subtract(ray, &mult);
	return (reflected);
}

t_color ft_color_addition(t_color *light_col, t_color *object_col)
{
	t_color color;

	color.x = object_col->x  + light_col->x;
	if (color.x  > 255)
		color.x = 255;
	color.y = object_col->y  + light_col->y;
	if (color.y  > 255)
		color.y = 255;
	color.z = object_col->z + light_col->z;
	if (color.z > 255)
		color.z = 255;
	return (color);
}

t_color ft_color_multiplication(t_color *light_col, double scalar)
{
	t_color color;

	color.x = light_col->x * scalar;
	if (color.x  > 255)
		color.x = 255;
	color.y = light_col->y * scalar;
	if (color.y  > 255)
		color.y = 255;
	color.z = light_col->z * scalar;
	if (color.z > 255)
		color.z = 255;
	return (color);
}

void apply_light(t_scene *scene, t_light *light, t_color *color, t_ray *ray, double distance, t_vector * normal)
{
	t_vector light_ray;
	t_vector minus_d;
	t_point point;

	t_color ambient;
	t_color diffuse;
	t_color specular;

	t_color effective_color;

	point = ray_position(ray, distance);
	light_ray = subtract(&point, &(light->object.center));
	normalize(&light_ray);

	effective_color = ft_color_multiplication(color, light->bright);
	minus_d = multiply_on_scalar(ray->direction, -1);
	if (dot(&light_ray, normal) < 0)
	{
		diffuse = new_tuple(0, 0 ,0, COLOR);
		specular = new_tuple(0, 0 ,0, COLOR);
	}
	else
	{
		diffuse = multiply_on_scalar(&effective_color, dot(&light_ray, normal));
		t_vector minus_light = multiply_on_scalar(&light_ray, -1);
//		t_vector minus_light = subtract(&(light->object.center), &point);
		t_vector reflected = reflect(&minus_light, normal);
		if (dot(&reflected, &minus_d) <= 0)
			specular = new_tuple(0, 0, 0, COLOR);
		else {
			double factor = ft_pow(dot(&reflected, &minus_d), 50);
			specular = multiply_on_scalar(&light->object.color, factor);
		}
	}
	*color = ft_color_addition(color, &diffuse);
	*color = ft_color_addition(color, &specular);
//	*color = ft_color_addition(&diffuse, &specular);
//	color = &diffuse;
}


int	lightning(t_scene *scene, t_object *object, t_ray *ray, double distance)
{
	t_light	*light_ptr;
	t_color	color;
	t_vector normal;
	t_point point;
//	t_color	effective_color;
//	t_vector light_vector;
//
//	t_color ambient;
//	t_color diffuse;
//	t_color specular;
//
	color = object->color;
	point = ray_position(ray, distance);
	normal = normal_at(object, &point);
	light_ptr = scene->l_lights;
	color = ft_color_multiplication(&color, scene->a_light.ratio);
	while (light_ptr)
	{
		apply_light(scene, light_ptr, &color, ray, distance, &normal);
		light_ptr = (t_light *)light_ptr->object.next;
	}
	return (ft_convert_rgb_int(color));
//	t_point point = ray_position(ray, distance);
//
////	t_color light_color = multiply_on_scalar(&(scene->l_lights->object.color), scene->l_lights->bright);
//	t_color light_color = scene->l_lights->object.color;
//	effective_color = ft_color_addition(&(object->color), &light_color);
//	light_vector = subtract(&(scene->l_lights->object.center), &point);
//	normalize(&light_vector);
//
//	ambient = multiply_on_scalar(&effective_color, scene->a_light.ratio);
//	t_vector normal = normal_at(object, &point);
//	if (dot(&light_vector, &normal) < 0)
//	{
//		diffuse = new_tuple(0, 0 ,0, COLOR);
//		specular = new_tuple(0, 0 ,0, COLOR);
//	}
//	else
//	{
//		diffuse = multiply_on_scalar(&effective_color, scene->l_lights->bright * dot(&light_vector, &normal));
//		t_vector minus_light = multiply_on_scalar(&light_vector, -1);
//		t_vector reflected = reflect(&minus_light, &normal);
//		if (dot(&reflected, ray->direction) <= 0)
//		{
//			specular = new_tuple(0, 0, 0, COLOR);
//		}
//		else
//		{
//			double factor = ft_pow(dot(&reflected, ray->direction), (int)object->shine);
//			specular = multiply_on_scalar(&light_color, factor);
//		}
//	}
//	color = ft_color_addition(&color, &ambient);
//	color = ft_color_addition(&color, &diffuse);
//	color = ft_color_addition(&color, &specular);
//	color = ft_color_addition(&ambient, &diffuse);
//	color = add(&ambient, &diffuse);
//	color = add(&color, &specular);
}
