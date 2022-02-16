//
// Created by atory on 19.01.2022.
//

#include "minirt.h"
#include "stdlib.h"

int	key_hook(int keycode, t_scene *scene)
{
//	printf("%d\n", keycode);
	if (keycode == 65307 || keycode == 53)
		exit(0);
	if (keycode == 13 || keycode == 119) // W
		scene->camera.center.y -= 0.2;
//	if (keycode == 13 || keycode == 119) // W
//		scene->camera.center.z -= 0.5;
	if (keycode == 0 || keycode == 97) // A
		scene->camera.center.x += 0.2;
	if (keycode == 1 || keycode == 115) // S
		scene->camera.center.y += 0.2;
//	if (keycode == 1 || keycode == 115) // S
//		scene->camera.center.z += 0.5;
	if (keycode == 2 || keycode == 100) // D
		scene->camera.center.x -= 0.2;
	if (keycode == 123 || keycode == 65361) // left arrow
		scene->view.rotation_y += 10;
	if (keycode == 124 || keycode == 65363) // right arrow
		scene->view.rotation_y -= 10;
	if (keycode == 126 || keycode == 65362) // up arrow
		scene->view.rotation_x += 10;
	if (keycode == 125 || keycode == 65364) // down arrow
		scene->view.rotation_x -= 10;
	if (keycode >= 123 && keycode <= 126)
		scene->view.rotate = new_rotation_matrix(scene->view.rotation_x,
												   scene->view.rotation_y,
												   scene->view.rotation_z);
//	calculate_view_reference(rt); // todo: free vectors
	new_image(scene);
}

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	if (button == 7)
		scene->camera.center.x -= 0.01;
	if (button == 6)
		scene->camera.center.x += 0.01;
	if (button == 4)
		scene->camera.center.z -= 0.2;
	if (button == 5)
		scene->camera.center.z += 0.2;
	new_image(scene);
//	printf("%d, %d, %d\n", button, x, y);
}

void free_scene(t_scene *scene)
{
	t_light		*ptr_light;
	t_light		*tmp;
	t_object	*tmp_object;
	t_object	*ptr_object;

//	mlx_destroy_window(scene->mlx, scene->win);
	ptr_light = scene->lights;
	while (ptr_light)
	{
		tmp = ptr_light;
		ptr_light = ptr_light->next;
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
	if (!scene.camera.ident)
		exception(NO_VAL, "Camera", 1);
	if (!init_mlx(&scene))
		exception(MLX, NULL, 1);
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
