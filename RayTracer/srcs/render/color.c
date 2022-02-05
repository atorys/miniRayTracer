//
// Created by atory on 27.01.2022.
//

#include "minirt.h"

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