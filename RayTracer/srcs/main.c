//
// Created by atory on 19.01.2022.
//

#include "minirt.h"
#include "get_next_line.h"
#include "stdlib.h"

int	key_hook(int keycode, t_scene *scene)
{
//	printf("%d\n", keycode);
	scene->view.rotation = scene->view.no_rotation;
	if (keycode == 65307 || keycode == 53)
		exit(0);
	if (keycode == 13 || keycode == 119) // W
		scene->camera.object.center.z--;
	if (keycode == 0 || keycode == 97) // A
		scene->camera.object.center.x += 0.2;
	if (keycode == 1 || keycode == 115) // S
		scene->camera.object.center.z++;
	if (keycode == 2 || keycode == 100) // D
		scene->camera.object.center.x -= 0.2;
//	if (keycode == 123) // left arrow
//	{
//		scene->view.rotation = scene->view.rotation_y_left;
//	}
//	if (keycode == 124) // right arrow
//	{
//		scene->view.rotation = scene->view.rotation_y_right;
//	}
	if (keycode == 126) // up arrow
	{
		scene->view.rotation_angle += 10;
		scene->view.rotation = new_rotation_matrix(0, 0, scene->view.rotation_angle);
	}
	if (keycode == 125) // down arrow
	{
		scene->view.rotation_angle -= 10;
		scene->view.rotation = new_rotation_matrix(0, 0, scene->view.rotation_angle);
	}

//	calculate_view_reference(rt); // todo: free vectors
	new_image(scene);
}

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	printf("%d, %d, %d\n", button, x, y);
}

int	calculate_view_reference(t_scene *scene)
{
	scene->view.width = tan(scene->camera.view_degree / 2 * (PI / 180)) * 2;
	scene->view.height = (double)scene->height / scene->width * scene->view.width;
	scene->view.x_change = scene->view.width / scene->width;
	scene->view.y_change = scene->view.height / scene->height;

	scene->view.rotation_angle = 0;
	scene->view.no_rotation = new_identity_matrix(4);
	scene->view.rotation = scene->view.no_rotation;
	if (!scene->view.no_rotation)
		return (0);
	return (1);
}

void free_scene(t_scene *scene)
{
	t_light		*ptr_light;
	t_light		*tmp;
	t_object	*tmp_object;
	t_object	*ptr_object;

	mlx_destroy_window(scene->mlx, scene->win);
	ptr_light = scene->l_lights;
	while (ptr_light)
	{
		tmp = ptr_light;
		ptr_light = (t_light *)ptr_light->object.next;
		free(tmp);
		tmp = NULL;
	}
	ptr_object = scene->object;
	while (ptr_object)
	{
		tmp_object = ptr_object;
		ptr_object = ptr_object->next;
		free(tmp_object);
		tmp_object = NULL;
	}
}

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
		exception(ARGUMENT, NULL, 1);
	init_scene(&scene);
	if (!(convert_file(av[1], &scene)))
		exception(NULL, NULL, 1);
	if (!scene.camera.object.ident)
		exception(NO_VAL, "Camera", 1);
	if (!init_mlx(&scene))
		exception(MLX, NULL, 1);

//	t_sphere sphere;
//	sphere.object.ident = sp;
//	sphere.object.center = (t_point){0, 0, 0, POINT};
//	sphere.object.next = NULL;
//	sphere.diameter = 2;
//	sphere.object.color = (t_color){255, 0, 0, COLOR};
//	sphere.object.intersection_func = intersect_sp;

//	t_point point = new_tuple(1, 0, 0, POINT);
//	t_vector normal = normal_at(&sphere, &point);
//	printf("%f ", normal.x);
//	printf("%f ", normal.y);
//	printf("%f ", normal.z);
//	printf("%f \n", normal.w);

	if (!calculate_view_reference(&scene))
		exception(MALLOC, NULL, 1);
	new_image(&scene);
	mlx_key_hook(scene.win, key_hook, &scene);
	mlx_mouse_hook(scene.win, mouse_hook, &scene);
	mlx_hook(scene.win, 17, 0, (void *)exit, NULL);
	mlx_loop(scene.mlx);
	free_scene(&scene);
	return 0;
}
