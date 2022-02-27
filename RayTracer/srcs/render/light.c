/****************************************************************************
 *		Вычисление цвета пикселя :	смешение цветов и наложение				*
 *									света / теней							*
 ****************************************************************************/
//
// Created by Achiote Tory on 1/22/22.
//

#include "render.h"

/*
 * Applying light color regarding !distance! between
 * light point and colored point
 */
static void 	apply_light(t_light *light, t_color *color, t_comp *computations)
{
	t_vector	light_ray;
	t_color		diffuse;
	t_color		specular;
	double		cosine;
	double		distance;

	light_ray = subtract(&(light->center), &(computations->point));
	distance = pow(0.9, module_v(&light_ray));
	normalize(&light_ray);

	diffuse = new_tuple(0, 0, 0, COLOR);
	specular = new_tuple(0, 0 ,0, COLOR);

	cosine = dot(&light_ray, &(computations->normal));
	if (cosine >= 0)
	{
		diffuse = multiply_on_scalar(&(light->effective_color), cosine * distance);
		t_vector minus_light = multiply_on_scalar(&light_ray, -1);
		t_vector reflected = reflect(&minus_light, &(computations->normal));
		cosine = dot(&reflected, &(computations->eye_v));
		if (cosine > 0)
		{
			double factor = ft_pow(cosine, (int)computations->object->specular);
			specular = multiply_on_scalar(&(light->effective_color), factor * distance);
		}
	}
	*color = ft_color_addition(color, &diffuse);
	*color = ft_color_addition(color, &specular);
}

static void	apply_shadow(t_light *light, t_color *color)
{
	t_color 	shadow;

	shadow = multiply_on_scalar(color, light->bright * -1 * 0.05);
	*color = ft_color_addition(color, &shadow);
}

static bool	is_shadowed(t_scene *scene, t_light *light, t_point *point)
{
	t_vector	light_vector;
	double		distance;
	t_ray		ray;
	t_hit		h;

	light_vector = subtract(&(light->center), point);
	distance = module_v(&light_vector);
	normalize(&light_vector);
	ray = new_ray(point, &light_vector);
	h = new_hit(scene, &ray);
	if (h.object && h.pair.x < distance)
		return (true);
	return (false);
}

/*
 * Смешение цветов :
 * 					1) добавление ambient цвета
 * 					2) затемнение до общей освещенности сцены
 * 					3) наложение цвета/света/теней для КАЖДОГО источника
 */
t_color	lightning(t_scene *scene, t_comp *computations)
{
	t_light	*light_ptr;
	t_color	color;

	color = ft_color_addition(&(computations->object->color),
							  &(scene->ambient.effective_color));
	light_ptr = scene->lights;
	color = ft_color_multiplication(&color, scene->ambient.ratio);
	while (light_ptr)
	{
		if (!is_shadowed(scene, light_ptr, &(computations->over_point)))
			apply_light(light_ptr, &color, computations);
		else
			apply_shadow(light_ptr, &color);
		light_ptr = light_ptr->next;
	}
	return (color);
}
