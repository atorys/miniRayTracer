//
// Created by atory on 27.01.2022.
//

#include "render.h"

t_color	new_color(t_scene *scene, t_ray *ray, int recursion_depth)
{
	t_comp	computations;
	t_color	color;
	t_color	reflected_color;
	t_ray 	reflected_ray;

	prepare_computations(&computations, scene, ray);
	if (!computations.object)
		return ((t_color){0, 0, 0, COLOR});
	color = lightning(scene, &computations);
	if (recursion_depth <= 0 || computations.object->reflective < 0)
		return (color);

	reflected_ray = new_ray(&(computations.over_point), &computations.reflect_v);

	reflected_color = new_color(scene, &reflected_ray, recursion_depth - 1);
	reflected_color = ft_color_multiplication(&reflected_color, computations.object->reflective);
	color = ft_color_multiplication(&color, 1 - computations.object->reflective);

	return (ft_color_addition(&color, &reflected_color));
}

int	ft_convert_rgb_int(t_color color)
{
	return (((int)color.x << 16 | (int)color.y << 8 | (int)color.z));
}

t_color ft_color_addition(t_color *color_1, t_color *color_2)
{
	t_color color;

	color.x = color_2->x  + color_1->x;
	if (color.x  > 255)
		color.x = 255;
	color.y = color_2->y  + color_1->y;
	if (color.y  > 255)
		color.y = 255;
	color.z = color_2->z + color_1->z;
	if (color.z > 255)
		color.z = 255;
	return (color);
}

t_color ft_color_multiplication(t_color *color_1, double scalar)
{
	t_color color_2;

	color_2.x = color_1->x * scalar;
	if (color_2.x  > 255)
		color_2.x = 255;
	color_2.y = color_1->y * scalar;
	if (color_2.y  > 255)
		color_2.y = 255;
	color_2.z = color_1->z * scalar;
	if (color_2.z > 255)
		color_2.z = 255;
	return (color_2);
}