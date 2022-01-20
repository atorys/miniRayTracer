//
// Created by atory on 19.01.2022.
//

#include "minirt.h"
#include "get_next_line.h"
#include "stdlib.h"

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
//	if (!calculate_view_reference(&rt))
//		exception(MALLOC, NULL, 1);
//	render_new_image(&rt);
//	mlx_key_hook(scene.win, key_hook, &scene);
//	mlx_mouse_hook(scene.win, mouse_hook, &scene);
//	mlx_hook(scene.win, 17, 0, (void *)exit, NULL);
//	mlx_loop(scene.mlx);
	return 0;
}
