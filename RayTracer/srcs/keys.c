//
// Created by atory on 22.02.2022.
//

#include "minirt.h"
#include "render.h"
#include "objects.h"

int	key_hook(int keycode, t_scene *scene)
{
//	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W) // W
		scene->camera.center.y -= 0.2;
	if (keycode == KEY_A) // A
		scene->camera.center.x += 0.2;
	if (keycode == KEY_S) // S
		scene->camera.center.y += 0.2;
	if (keycode == KEY_D) // D
		scene->camera.center.x -= 0.2;
	if (keycode == KEY_ARROW_LEFT) // left arrow
		scene->view.rotation_y += 30;
	if (keycode == KEY_ARROW_RIGHT) // right arrow
		scene->view.rotation_y -= 30;
	if (keycode == KEY_ARROW_UP) // up arrow
		scene->view.rotation_x += 30;
	if (keycode == KEY_ARROW_DOWN) // down arrow
		scene->view.rotation_x -= 30;
//	if (keycode >= 123 && keycode <= 126)
	scene->view.rotate = new_rotation_matrix(scene->view.rotation_x,
											 scene->view.rotation_y,
											 scene->view.rotation_z);
	new_image(scene);
}

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;

	if (button == 7)
		scene->camera.center.x -= 0.01;
	if (button == 6)
		scene->camera.center.x += 0.01;
	if (button == KEY_ZOOM_IN)
		scene->camera.center.z += 0.5;
	if (button == KEY_ZOOM_OUT)
		scene->camera.center.z -= 0.5;
	if (button == KEY_MOUSE_LEFT || button == KEY_MOUSE_RIGHT)
	{
		ray = trace_ray(&(scene->camera.center),
						x - (scene->width/2),
						(y - (scene->height/2)) * -1,
						&(scene->view));
		hit = new_hit(scene, &ray);
		if (hit.object)
		{
			if (button == KEY_MOUSE_RIGHT)
				resize(hit.object, 0.5);
			else
				resize(hit.object, -0.5);
			new_image(scene);
		}
	}
//	printf("%d, %d, %d\n", button, x, y);
	new_image(scene);
}
