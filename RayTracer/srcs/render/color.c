//
// Created by atory on 27.01.2022.
//

#include "minirt.h"

int	ft_convert_rgb_int(t_color color)
{
	return (((int)color.x << 16 | (int)color.y << 8 | (int)color.z));
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