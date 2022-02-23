/****************************************************************************
 *			Функции изменения размера  фигур :			сферы				*
 *														плоскости			*
 *														цилиндра			*
 ****************************************************************************/
//
// Created by atory on 23.02.2022.
//

#include "render.h"

/*
 * Общий вызов функции изменения размера
 * через внутренний указатель на функцию каждого обЬекта
 */
void	resize(t_object* this, double size)
{
	this->resize_func(this, size);
}

void	resize_sp(void* this, double size)
{
	t_sphere *sphere;

	sphere = (t_sphere *)this;
	if (sphere->diameter + size <= EPSILON)
		return ;
	sphere->diameter += size;
	sphere->squared_radius = (sphere->diameter/2) * (sphere->diameter/2);
}

void	resize_pl(void* this, double size)
{
}

void	resize_cy(void* this, double size)
{
	t_cylinder *cylinder;

	cylinder = (t_cylinder *)this;
	if (cylinder->diameter + size <= EPSILON)
		return ;
	cylinder->diameter += size;
	cylinder->squared_radius = (cylinder->diameter/2) * (cylinder->diameter/2);
}
