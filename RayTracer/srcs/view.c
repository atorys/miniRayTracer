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
	t_vector up;
	t_vector forward;

	scene->camera = *(scene->cameras);
	scene->view.width = tan(scene->camera.view_degree / 2 * (PI / 180)) * 2;
	scene->view.height = (double)scene->height / scene->width * scene->view.width;
	scene->view.x_change = scene->view.width / scene->width;
	scene->view.y_change = scene->view.height / scene->height;

	scene->view.rotation_x = 0;
	scene->view.rotation_y = 0;
	scene->view.rotation_z = 0;

	forward = scene->camera.orientation;
	up = (t_vector){0, 1, 0, VECTOR};
	if (forward.x == 0 && (forward.y == 1 || forward.y == -1) && forward.z == 0)
	{
		if (forward.y == 1)
			up.z = -1;
		else
			up.z = 1;
		up.y = 0;
	}
	free_matrix(scene->view.rotate);
	scene->view.rotate = new_identity_matrix(4);
	free_matrix(scene->view.transform);
	scene->view.transform = transform_view(&(scene->camera.center),
										  &(forward),
										  up);
	if (!scene->view.rotate || !scene->view.transform)
		return (0);
	return (1);
}

t_matrix	*transform_view(t_point *from, t_vector *forward, t_vector up)
{
	t_vector left;
	t_vector true_up;
	t_matrix *orientation;
	t_matrix *translation;
	t_matrix *transform;

	if (forward->x == 0 && (forward->y == 1 || forward->y == -1) && forward->z == 0)
	{
		if (forward->y == 1)
			up.z = -1;
		else
			up.z = 1;
		up.y = 0;
	}
	left = cross(forward, &up);
	true_up = cross(&left, forward);
	orientation = new_orientation_matrix(&left, &true_up, forward);
	translation = new_translation_matrix((from->x), (from->y),(from->z));
	if (!orientation || !translation)
		return (NULL);
	transform = multiply_matrix(translation, orientation);
	if (!transform)
		return (NULL);
	return (transform);
//	return (orientation);
}
