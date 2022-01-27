//
// Created by atory on 27.01.2022.
//

#include "tuple.h"

double  module_v(const t_vector* vector)
{
	return (sqrt((vector->x * vector->x) +
				 (vector->y * vector->y) +
				 (vector->z * vector->z) +
				 (vector->w * vector->w)));
}

void    normalize(t_vector *vector)
{
	double	module;

	module = module_v(vector);
	if (!module)
		return ;
	vector->x /= module;
	vector->y /= module;
	vector->z /= module;
	vector->w /= module;
}

double	dot(const t_vector* vector1, const t_vector* vector2)
{
	return (vector1->x * vector2->x +
			vector1->y * vector2->y +
			vector1->z * vector2->z +
			vector1->w * vector2->w);
}

/*                             v1  v2
 * Векторное умножение         |  /
 * @param v1 - первый вектор   | /
 * @param v2 - второй          |/______v3
 * @return вектор v3 перпендикулярный v1 и v2
 */
t_vector	cross(const t_vector* vector1, const t_vector* vector2)
{
	t_vector	v3;
	v3 = new_tuple((vector1->y * vector2->z) - (vector1->z * vector2->y),
				   (vector1->z * vector2->x) - (vector1->x * vector2->z),
				   (vector1->x * vector2->y) - (vector1->y * vector2->x),
				   VECTOR);
	return (v3);
}

t_vector	reflect(const t_vector* ray, const t_vector* normal)
{
	t_vector reflected;

	t_vector mult = multiply_on_scalar(normal, 2 * dot(ray, normal));
	reflected = subtract(ray, &mult);
	return (reflected);
}
