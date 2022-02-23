//
// Created by atory on 19.01.2022.
//

#include "minirt.h"
#include "render.h"
#include "stdlib.h"

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
