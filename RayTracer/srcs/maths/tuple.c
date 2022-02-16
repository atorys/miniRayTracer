/****************************************************************************
 * 		Создание, сравнение, добавление, вычитание, умножение на			*
 * 		скаляр кортежей														*
 ****************************************************************************/
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
