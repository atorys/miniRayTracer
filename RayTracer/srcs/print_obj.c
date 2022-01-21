//
// Created by atory on 19.01.2022.
//

#include "minirt.h"

void	print_object(t_object*	this) {
	this->print_func(this);
}

void	print_object_default(void * this_ptr) {
	t_object *object = (t_object *)this_ptr;
	printf("id = %d\n", object->ident);
	printf("center = %f, %f, %f\n", object->center.x, object->center.y, object->center.z);
}

void	print_sphere(void * this_ptr) {
	printf("SPHERE\n");
	print_object_default(this_ptr);

	t_sphere *sphere = (t_sphere *)this_ptr;
	printf("diameter = %f\n", sphere->diameter);
	printf("color = %f, %f, %f\n\n", sphere->object.color.x, sphere->object.color.y, sphere->object.color.z);
}

void	print_plane(void * this_ptr) {
	printf("PLANE\n");
	print_object_default(this_ptr);

	t_plane *plane = (t_plane *)this_ptr;
	printf("orientation = %f, %f, %f\n", plane->orientation.x, plane->orientation.y, plane->orientation.z);
	printf("color = %f, %f, %f\n\n", plane->object.color.x, plane->object.color.y, plane->object.color.z);
}

void	print_cylinder(void * this_ptr) {
	printf("CYLINDER\n");
	print_object_default(this_ptr);

	t_cylinder *cylinder = (t_cylinder *)this_ptr;
	printf("orientation = %f, %f, %f\n", cylinder->orientation.x, cylinder->orientation.y, cylinder->orientation.z);
	printf("diameter = %f\n", cylinder->diameter);
	printf("diameter = %f\n", cylinder->height);
	printf("color = %f, %f, %f\n\n", cylinder->object.color.x, cylinder->object.color.y, cylinder->object.color.z);
}

void	print_camera(void * this_ptr) {
	printf("CAMERA\n");
	print_object_default(this_ptr);

	t_camera *camera = (t_camera *)this_ptr;
	printf("orientation = %f, %f, %f\n\n", camera->orientation.x, camera->orientation.y, camera->orientation.z);
}
