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

	color.x = object_col->x * (light_col->x / 255);
	if (color.x  > 255)
		color.x = 255;
	color.y = object_col->y * (light_col->y / 255);
	if (color.y  > 255)
		color.y = 255;
	color.z = object_col->z * (light_col->z / 255);
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


int	lightning(t_scene *scene, t_object *object, t_ray *ray, double distance)
{
	t_light	*light_ptr;
	t_color	color;
	t_color	effective_color;
	t_vector light_vector;

	t_color ambient;
	t_color diffuse;
	t_color specular;

//	light_ptr = scene->l_lights;
	color = object->color;
	t_point point = ray_position(ray, distance);

//	t_color light_color = multiply_on_scalar(&(scene->l_lights->object.color), scene->l_lights->bright);
	t_color light_color = scene->l_lights->object.color;
	effective_color = ft_color_addition(&(object->color), &light_color);
	light_vector = subtract(&(scene->l_lights->object.center), &point);
	normalize(&light_vector);

	ambient = multiply_on_scalar(&effective_color, scene->a_light.ratio);
	t_vector normal = normal_at(object, &point);
	if (dot(&light_vector, &normal) < 0)
	{
		diffuse = new_tuple(0, 0 ,0, COLOR);
		specular = new_tuple(0, 0 ,0, COLOR);
	}
	else
	{
		diffuse = multiply_on_scalar(&effective_color, scene->l_lights->bright * dot(&light_vector, &normal));
		t_vector minus_light = multiply_on_scalar(&light_vector, -1);
		t_vector reflected = reflect(&minus_light, &normal);
		if (dot(&reflected, ray->direction) <= 0)
		{
			specular = new_tuple(0, 0, 0, COLOR);
		}
		else
		{
			double factor = ft_pow(dot(&reflected, ray->direction), (int)object->shine);
			specular = multiply_on_scalar(&light_color, factor);
		}
	}
//	while (light_ptr)
//	{
//
//		light_ptr = (t_light *)light_ptr->object.next;
//	}
	color = ft_color_addition(&ambient, &diffuse);
	color = add(&color, &specular);
	return (ft_convert_rgb_int(color));
}
