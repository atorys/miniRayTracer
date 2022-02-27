/****************************************************************************
 * 	Расчет высоты и ширины рамки просмотра в трехмерном пространстве для	*
 *	проекции на двумерную плоскость холста с учетом угла просмотра камеры	*
 * 																			*
 * 	Нахождение коэффициентов для перевода точки трехмерного пространства	*
 * 	в точку двумерной плоскости холста										*
 * 																			*
 * 	Расчет нового базиса относительно положения камеры в пространстве		*
 * 	Построение на его основе матрицы перехода вектора в новый базис			*
 ****************************************************************************/
//
// Created by atory on 05.02.2022.
//

#include "minirt.h"

int	calculate_view_reference(t_scene *scene)
{
	scene->camera = *(scene->cameras);
	scene->view.width = tan(scene->camera.view_degree / 2 * (PI / 180)) * 2;
	scene->view.height = (double)scene->height / scene->width * scene->view.width;
	scene->view.x_change = scene->view.width / scene->width;
	scene->view.y_change = scene->view.height / scene->height;

	scene->view.rotation_x = 0;
	scene->view.rotation_y = 0;

	free_matrix(scene->view.rotate);
	scene->view.rotate = new_identity_matrix(4);
	free_matrix(scene->view.transform);
	scene->view.transform = transform_view(&(scene->camera.center),
										  &(scene->camera.orientation),
										   (t_vector){0, 1, 0, VECTOR});
	if (!scene->view.rotate || !scene->view.transform)
		return (ERROR);
	return (SUCCESS);
}

t_matrix	*transform_view(t_point *from, t_vector *forward, t_vector up)
{
	t_vector left;
	t_vector true_up;
	t_matrix *orientation;
	t_matrix *translation;
	t_matrix *transform;

	if (compare_tuples(forward, &(t_tuple){0, 1, 0, VECTOR}))
		up = (t_vector){0, 0, -1, VECTOR};
	else if (compare_tuples(forward, &(t_tuple){0, -1, 0, VECTOR}))
		up = (t_vector){0, 0, 1, VECTOR};
	left = cross(forward, &up);
	true_up = cross(&left, forward);
	orientation = new_orientation_matrix(&left, &true_up, forward);
	translation = new_translation_matrix((from->x), (from->y),(from->z));
	if (!orientation || !translation)
		return (NULL);
	transform = multiply_matrix(translation, orientation);
	if (!transform)
		return (NULL);
	free_matrix(orientation);
	free_matrix(translation);
	return (transform);
}
