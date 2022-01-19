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
	double **a;
	int size;
	double det;
};

t_matrix*	new_matrix(int size);
t_matrix*	submatrix(t_matrix *matrix, int i, int j);
void		free_matrix(t_matrix *matrix);

bool		compare_matrix(t_matrix *matrix1, t_matrix *matrix2);

t_matrix*	multiply_matrix(t_matrix *matrix1, t_matrix *matrix2);
t_tuple*	multiply_matrix_tuple(t_matrix *matrix, t_tuple* tuple);

void		transpose(t_matrix **matrix);
double 		determinant(t_matrix *matrix, int depth);

#endif
