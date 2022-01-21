//
// Created by atory on 17.01.2022.
//

#include "tuple.h"

/*
 * POINT : W = 1
 * VECTOR : W = 0
 */
t_tuple	new_tuple(double x, double y, double z, double type)
{
	t_tuple	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = type;
	return (new);
}

bool	compare_tuples(const t_tuple *tuple1, const t_tuple *tuple2)
{
	return (ft_equal(tuple1->x, tuple2->x) &&\
			ft_equal(tuple1->y, tuple2->y) &&\
			ft_equal(tuple1->z, tuple2->z) &&\
			ft_equal(tuple1->w, tuple2->w));
}

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

/*
 * POINT (W = 1) + VECTOR (W = 0) = POINT (W = 1)
 * VECTOR (W = 0) + VECTOR (W = 0) = VECTOR (W = 0)
 */
t_tuple	add(const t_tuple *tuple1, const t_tuple *tuple2)
{
	t_tuple	t3;

	t3 = new_tuple(tuple1->x + tuple2->x,
			   tuple1->y + tuple2->y,
			   tuple1->z + tuple2->z,
			   tuple1->w + tuple2->w);
	return (t3);
}

/*
 * POINT - VECTOR = POINT (W = 1)
 * POINT - POINT = VECTOR (W = 1)
 * VECTOR - VECTOR = VECTOR (W = 0)
 *
 *                                 v2
 * Вычитание векторов              |\
 * @param v1 - первый вектор   	   | \
 * @param v2 - второй              |__\_v1
 * @return v3                         v3
 */
t_tuple	subtract(const t_tuple *tuple1, const t_tuple *tuple2)
{
	t_tuple t3;

	t3 = new_tuple(tuple1->x - tuple2->x,
			   tuple1->y - tuple2->y,
			   tuple1->z - tuple2->z,
			   tuple1->w - tuple2->w);
	return (t3);
}

void	scale(t_tuple *tuple, double scalar)
{
	tuple->x *= scalar;
	tuple->y *= scalar;
	tuple->z *= scalar;
//	(*tuple)->w *= scalar;
}

t_tuple   multiply_on_scalar(const t_tuple *tuple1, double scalar)
{
	t_tuple tuple2;

	tuple2 = new_tuple(tuple1->x * scalar,
				   tuple1->y * scalar,
				   tuple1->z * scalar,
				   tuple1->w);
	return (tuple2);
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
