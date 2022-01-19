//
// Created by atory on 17.01.2022.
//

#ifndef TUPLE_H
#define TUPLE_H

# include <math.h>
# include "maths.h"
# include <stdlib.h>

# define VECTOR	0
# define POINT	1
# define COLOR	3.3

typedef struct s_base_tuple	t_tuple;

typedef t_tuple				t_vector;
typedef t_tuple				t_point;
typedef t_tuple				t_color;

struct	s_base_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
};

t_tuple*	new_tuple(double x, double y, double z, double type);

bool		compare_tuples(const t_tuple *tuple1, const t_tuple *tuple2);

double 		module_v(const t_vector* vector);
void		normalize(t_vector **vector);

double		dot(const t_tuple *tuple1, const t_tuple *tuple2);
t_tuple*	add(const t_tuple *tuple1, const t_tuple *tuple2);
t_tuple*	subtract(const t_tuple *tuple1, const t_tuple *tuple2);
void		scale(t_tuple **tuple, double scalar);
t_tuple*	multiply_on_scalar(const t_tuple *tuple, double scalar);

t_vector	*cross(const t_vector* vector1, const t_vector* vector2);

#endif
