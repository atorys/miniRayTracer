//
// Created by atory on 17.01.2022.
//

#include "matrix.h"

t_matrix*	new_matrix(int size)
{
	t_matrix*	new;
	int 		i;

	new = malloc(sizeof(t_matrix));
	if (!new)
		return (NULL);
	new->size = size;
	new->a = (double**)malloc(sizeof(double *) * size);
	i = -1;
	while (++i < size)
	{
		new->a[i] = (double *)malloc(sizeof(double) * size);
		if (!new->a[i])
			return (NULL);
	}
	return (new);
}

t_matrix*	submatrix(t_matrix *matrix, int i, int j)
{
	t_matrix*	new;
	int 		n;
	int 		m;
	int 		skip_i;
	int 		skip_j;

	new = new_matrix(matrix->size - 1);
	if (!new)
		return (NULL);
	n = -1;
	skip_i = 0;
	while (++n < new->size)
	{
		skip_j = 0;
		m = -1;
		while (++m < new->size) {
			if (n == i)
				skip_i = 1;
			if (m == j)
				skip_j = 1;
			new->a[i][j] = matrix->a[n + skip_i][m + skip_j];
		}
	}
	return (new);
}

void		free_matrix(t_matrix *matrix)
{
	int i;

	i = -1;
	while (++i < matrix->size)
	{
		free(matrix->a[i]);
		matrix->a[i] = NULL;
	}
	free(matrix->a);
	matrix = NULL;
	free(matrix);
	matrix = NULL;
}

bool		compare_matrix(t_matrix *matrix1, t_matrix *matrix2)
{
	int	i;
	int j;

	if (matrix1->size != matrix2->size)
		return (false);
	i = -1;
	while (++i < matrix1->size)
	{
		j = -1;
		while (++j < matrix1->size)
		{
			if (!ft_equal(matrix1->a[i][j], matrix2->a[i][j]))
				return (false);
		}
	}
	return (true);
}

t_matrix*	multiply_matrix(t_matrix *matrix1, t_matrix *matrix2)
{
	t_matrix*	result;
	double		element;
	int 		i;
	int 		j;
	int 		k;

	result = new_matrix(matrix1->size);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < matrix1->size)
	{
		j = -1;
		while (++j < matrix1->size)
		{
			element = 0;
			k = -1;
			while (++k < matrix1->size)
				element += matrix1->a[i][k] * matrix2->a[k][j];
			result->a[i][j] = element;
		}
	}
	return (result);
}

t_tuple*	multiply_matrix_tuple(t_matrix *matrix, t_tuple* tuple)
{
	t_tuple*	result;
	double		array[4];
	int 		i;

	result = new_tuple(0, 0, 0, 0);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < matrix->size)
	{
		array[i] = (matrix->a[i][0] * tuple->x) + (matrix->a[i][1] * tuple->y) +
					(matrix->a[i][2] * tuple->z) + (matrix->a[i][3] * tuple->w);
	}
	result->x = array[0];
	result->y = array[1];
	result->z = array[2];
	result->w = array[3];
	return (result);
}
#include "stdio.h"

void	transpose(t_matrix **matrix)
{
	double	tmp;
	int		i;
	int 	j;

	i = 0;
	while (i < (*matrix)->size)
	{
		j = i;
		while (j < (*matrix)->size)
		{
			tmp = (*matrix)->a[i][j];
			(*matrix)->a[i][j] = (*matrix)->a[j][i];
			(*matrix)->a[j][i] = tmp;
			j++;
		}
		i++;
	}
}

double 		determinant(t_matrix *matrix, int depth)
{
	if (depth == 2)
		return ((matrix->a[0][0] * matrix->a[1][1]) -
				(matrix->a[0][1] * matrix->a[1][0]));
//	if (depth == 2)
//		return ((matrix->a[0 + i_sub][0 + j_sub] * matrix->a[1 + i_sub][1 + j_sub]) -
//				(matrix->a[0 + i_sub][1 + j_sub] * matrix->a[1 + i_sub][0 + j_sub]));
//	else if (depth == 3)
//		return (((matrix->a[0][0] * matrix->a[1][1] * matrix->a[2][2]) +
//				(matrix->a[0][1] * matrix->a[1][2] * matrix->a[2][0]) +
//				(matrix->a[0][2] * matrix->a[1][0] * matrix->a[2][1]))
//				-
//				((matrix->a[0][2] * matrix->a[1][2]* matrix->a[2][0])))

//	return (matrix->a[0][0] * determinant(matrix, 2, 1, 1) +
//			matrix->a[1][0] * determinant(matrix, 2, 1, 1) +);
}