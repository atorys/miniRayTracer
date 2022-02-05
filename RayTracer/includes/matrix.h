//
// Created by atory on 17.01.2022.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "maths.h"
#include "tuple.h"

typedef struct s_matrix	t_matrix;

struct	s_matrix
{
	double	**a;
	int		size;
	double	det;
};

t_matrix*	new_matrix(int size);
t_matrix*	new_identity_matrix(int size);
t_matrix*	new_translation_matrix(double x, double y, double z);
t_matrix*	new_scaling_matrix(double x, double y, double z);
t_matrix*	new_rotation_matrix(double x_axis, double y_axis, double z_axis);
t_matrix*	new_orientation_matrix(t_vector *left, t_vector *up, t_vector *forward);
void		free_matrix(t_matrix *matrix);

bool		compare_matrix(t_matrix *matrix1, t_matrix *matrix2);

t_matrix*	multiply_matrix(t_matrix *matrix1, t_matrix *matrix2);
t_tuple		multiply_matrix_tuple(t_matrix *matrix, t_tuple* tuple);

void		transpose(t_matrix **matrix);
double 		determinant(t_matrix *matrix);
double 		minor(t_matrix *matrix, int i, int j);
t_matrix*	submatrix(t_matrix *matrix, int i, int j);

t_matrix*	inverse(t_matrix *matrix);

#endif
