/****************************************************************************
 * 			Создание квадратной матрицы пользовательского размера,			*
 * 			заполнена нулями, создание единичной матрицы, матрицы 			*
 * 			перемещения, трансформации точек и векторов, матрицы  			*
 * 			трансформации вектора в новый базис                   			*
 * 			                                                      			*
 * 			Сравнение матриц                                      			*
 * 			Умножение матрицы на кортеж, на другую матрицу        			*
 * 			Транспонирование, инвертирование                      			*
 * 			Нахождение подматрицы, определителя и минора          			*
 ****************************************************************************/

//
// Created by atory on 17.01.2022.
//

#include "matrix.h"

/*
 * zeroed square matrix size x size
 */
t_matrix*	new_matrix(int size)
{
	t_matrix*	new;
	int			i;
	int			j;

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
		j = -1;
		while (++j < size)
			new->a[i][j] = 0;
	}
	return (new);
}

/*
 * square matrix like
 *  | 1 0 0 |
 *  | 0 1 0 |
 *  | 0 0 1 |
 */
t_matrix*	new_identity_matrix(int size)
{
	t_matrix*	new;
	int 		i;

	new = new_matrix(size);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < size)
		new->a[i][i] = 1;
	return (new);
}

/*
 * matrix used for POINT translation
 *  | 1 0 0 x |
 *  | 0 1 0 y |
 *  | 0 0 1 z |
 *  | 0 0 0 1 |
 */
t_matrix*	new_translation_matrix(double x, double y, double z)
{
	t_matrix*	new;

	new = new_identity_matrix(4);
	if (!new)
		return (NULL);
	new->a[0][3] = x;
	new->a[1][3] = y;
	new->a[2][3] = z;
	return (new);
}

/*
 * matrix used for POINT and VECTOR scaling
 *  | x 0 0 0 |
 *  | 0 y 0 0 |
 *  | 0 0 z 0 |
 *  | 0 0 0 1 |
 */
t_matrix*	new_scaling_matrix(double x, double y, double z)
{
	t_matrix*	new;

	new = new_identity_matrix(4);
	if (!new)
		return (NULL);
	new->a[0][0] = x;
	new->a[1][1] = y;
	new->a[2][2] = z;
	return (new);
}

/*
 * matrix used for POINT and VECTOR rotation
 *
 * 	1) rotation matrix for X axis:
 *
 *  | 1   0 	 0     0 |
 *  | 0 cos(r) -sin(r) 0 |
 *  | 0 sin(r) cos(r)  0 |
 *  | 0   0      0     1 |
 *
 *  2) rotation matrix for Y axis:
 *
 *  | cos(r)  0 sin(r) 0 |
 *  |   0     1   0    0 |
 *  | -sin(r) 0 cos(r) 0 |
 *  |   0     0   0    1 |
 *
 * 3)  for both XY axis:
 *
 *  | cos(r)    0     sin(r) 0 |
 *  |   0     cos(r) -sin(r) 0 |
 *  | -sin(r) sin(r)  cos(r) 0 |
 *  |   0       0       0    1 |
 */
t_matrix*	new_rotation_matrix(double x_axis, double y_axis, double z_axis)
{
	t_matrix*	new;

	new = new_identity_matrix(4);
	if (!new)
		return (NULL);
	if (x_axis)
	{
		x_axis = radians(x_axis);
		new->a[1][1] = cos(x_axis);
		new->a[1][2] = -sin(x_axis);
		new->a[2][1] = sin(x_axis);
		new->a[2][2] = cos(x_axis);
	}
	if (y_axis)
	{
		y_axis = radians(y_axis);
		new->a[0][0] = cos(y_axis);
		new->a[0][2] = sin(y_axis);
		new->a[2][0] = -sin(y_axis);
		new->a[2][2] = cos(y_axis);
	}
	if (z_axis)
	{
		z_axis = radians(z_axis);
		new->a[0][0] = cos(z_axis);
		new->a[0][1] = -sin(z_axis);
		new->a[1][0] = sin(z_axis);
		new->a[1][1] = cos(z_axis);
	}
	return (new);
}

/*
 * matrix used for POINT and VECTOR orientation
 * in new basis vectors
 *
 * 	L - new left vector
 * 	U - true up vector
 * 	D - new forward vector
 *
 *  |  Lx  Ly  Lz  0 |
 *  |  Ux  Uy  Uz  0 |
 *  | -Dx -Dy -Dz  0 |
 *  |   0   0   0  1 |
 */
t_matrix*	new_orientation_matrix(t_vector *left, t_vector *up, t_vector *forward)
{
	t_matrix*	new;

	new = new_identity_matrix(4);
	if (!new)
		return (NULL);
	new->a[0][0] = left->x;
	new->a[0][1] = left->y;
	new->a[0][2] = left->z;
	new->a[1][0] = up->x;
	new->a[1][1] = up->y;
	new->a[1][2] = up->z;
	new->a[2][0] = -(forward->x);
	new->a[2][1] = -(forward->y);
	new->a[2][2] = -(forward->z);
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
		while (++m < new->size)
		{
			if (n == i)
				skip_i = 1;
			if (m == j)
				skip_j = 1;
			new->a[n][m] = matrix->a[n + skip_i][m + skip_j];
		}
	}
	return (new);
}

void		free_matrix(t_matrix *matrix)
{
	int i;

	i = -1;
	if (!matrix)
		return ;
	while (++i < matrix->size)
	{
		free(matrix->a[i]);
		matrix->a[i] = NULL;
	}
	free(matrix->a);
	matrix->a = NULL;
	free(matrix);
	matrix = NULL;
}

/*
 * returns TRUE if
 * 	1) matrices' sizes are the same
 * 	2) elements are equal
 * otherwise returns FALSE
 */
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

t_tuple	multiply_matrix_tuple(t_matrix *matrix, t_tuple* tuple)
{
	t_tuple	result;
	double	array[4];
	int 	i;

	result = new_tuple(0, 0, 0, 0);
	i = -1;
	while (++i < matrix->size)
	{
		array[i] = (matrix->a[i][0] * tuple->x) + (matrix->a[i][1] * tuple->y) +
					(matrix->a[i][2] * tuple->z) + (matrix->a[i][3] * tuple->w);
	}
	result.x = array[0];
	result.y = array[1];
	result.z = array[2];
	result.w = array[3];
	return (result);
}

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

double 		determinant(t_matrix *matrix)
{
	double	det;
	int		j;

	if (matrix->size == 2)
		return ((matrix->a[0][0] * matrix->a[1][1]) -
				(matrix->a[0][1] * matrix->a[1][0]));
	else
	{
		det = 0;
		j = -1;
		while (++j < matrix->size)
			det += matrix->a[0][j] * minor(matrix, 0, j) * ft_pow(-1, 0 + j);
	}
	return (det);
}

double 		minor(t_matrix *matrix, int i, int j)
{
	double		det;
	t_matrix	*sub;

	sub = submatrix(matrix, i, j);
	if (!sub) // todo: error up? exit?
		return (0);
	det = determinant(sub);
	free_matrix(sub);
	return (det);
}

t_matrix*	inverse(t_matrix *matrix)
{
	t_matrix	*new;
	double 		det;
	int			i;
	int			j;

	det = determinant(matrix);
	if (det == 0)
		return (NULL);
	new = new_matrix(matrix->size);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < new->size)
	{
		j = -1;
		while (++j < new->size)
			new->a[i][j] = minor(matrix, i, j) * ft_pow(-1, i + j) / det;
	}
	transpose(&new);
	return (new);
}
