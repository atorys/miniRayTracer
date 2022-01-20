//
// Created by atory on 19.01.2022.
//

#include "minirt.h"
#include "get_next_line.h"
#include "stdlib.h"

int	key_hook(int keycode, t_scene *scene)
{
//	printf("%d\n", keycode);
	if (keycode == 65307 || keycode == 53)
		exit(0);
	if (keycode == 13 || keycode == 119) // W
		scene->camera.object.center.z--;
	if (keycode == 0 || keycode == 97) // A
		scene->camera.object.center.x--;
	if (keycode == 1 || keycode == 115) // S
		scene->camera.object.center.z++;
	if (keycode == 2 || keycode == 100) // D
		scene->camera.object.center.x++;
//	calculate_view_reference(rt); // todo: free vectors
//	render_new_image(rt);
}

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	printf("%d, %d, %d\n", button, x, y);
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
//	if (!init_mlx(&scene))
//		exception(MLX, NULL, 1);
//	if (!calculate_view_reference(&rt))
//		exception(MALLOC, NULL, 1);
//	render_new_image(&rt);
//	mlx_key_hook(scene.win, key_hook, &scene);
//	mlx_mouse_hook(scene.win, mouse_hook, &scene);
//	mlx_hook(scene.win, 17, 0, (void *)exit, NULL);
//	mlx_loop(scene.mlx);

	t_matrix* matrix1 = new_matrix(4);
	t_matrix* matrix2 = new_matrix(4);
//
	matrix1->a[0][0] = 3;
	matrix1->a[0][1] = -9;
	matrix1->a[0][2] = 7;
	matrix1->a[0][3] = 3;

	matrix1->a[1][0] = 3;
	matrix1->a[1][1] = -8;
	matrix1->a[1][2] = 2;
	matrix1->a[1][3] = -9;

	matrix1->a[2][0] = -4;
	matrix1->a[2][1] = 4;
	matrix1->a[2][2] = 4;
	matrix1->a[2][3] = 1;

	matrix1->a[3][0] = -6;
	matrix1->a[3][1] = 5;
	matrix1->a[3][2] = -1;
	matrix1->a[3][3] = 1;
	//
	matrix2->a[0][0] = 8;
	matrix2->a[0][1] = 2;
	matrix2->a[0][2] = 2;
	matrix2->a[0][3] = 2;

	matrix2->a[1][0] = 3;
	matrix2->a[1][1] = -1;
	matrix2->a[1][2] = 7;
	matrix2->a[1][3] = 0;

	matrix2->a[2][0] = 7;
	matrix2->a[2][1] = 0;
	matrix2->a[2][2] = 5;
	matrix2->a[2][3] = 4;

	matrix2->a[3][0] = 6;
	matrix2->a[3][1] = -2;
	matrix2->a[3][2] = 0;
	matrix2->a[3][3] = 5;

	int	i;
	int j;

	i = -1;
//	while (++i < 4)
//	{
//		j = -1;
//		while (++j < 4)
//		{
//			printf("%f ", matrix1->a[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");

//	new->a[1][1] = 2;
	t_tuple *t = new_tuple(2, 3, 4, POINT);
	t_matrix *new = new_scaling_matrix(-1, 1, 1);

	t_tuple *mult = multiply_matrix_tuple(new, t);
	printf("%f ", mult->x);
	printf("%f ", mult->y);
	printf("%f ", mult->z);
	printf("%f ", mult->w);


//	while (scene.object)
//	{
//		print_object(scene.object);
//		scene.object = scene.object->next;
//	}

	return 0;
}
