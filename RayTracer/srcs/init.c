#include "minirt.h"

int	init_scene(t_scene *scene)
{
	scene->mlx = NULL;
	scene->win = NULL;
	scene->canvas.img = NULL;
	scene->canvas.addr = NULL;

	scene->height = WIN_HEIGHT;
	scene->width = WIN_WIDTH;

	scene->canvas.w = scene->width;
	scene->canvas.h = scene->height;

	scene->ambient.ident = 0;
	scene->camera_count = 0;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->object = NULL;

	scene->view.transform = NULL;
	scene->view.rotate = NULL;
	return (SUCCESS);
}

int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (ERROR);
	scene->win = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!scene->win)
		return (ERROR);
	return (SUCCESS);
}
