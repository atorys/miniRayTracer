//
// Created by Achiote Tory on 3/5/22.
//

#include "render.h"


static void	display_camera(t_scene *scene, double *data, int x, int y)
{
	int		i;
	int		offset;
	char	*string;

	i = -1;
	offset = 0;
	while (++i < 6)
	{
		if (i == 3)
		{
			offset = 15;
			x = 105;
		}
		string = ft_dtoa(data[i], 100);
		if (!string)
			exception(MALLOC, NULL, 1);
		mlx_string_put(scene->mlx, scene->win, x, y + offset,
					   COLOR_WHITE, string);
		x += 40;
		free(string);
	}
	string = ft_itoa(scene->camera.number);
	if (!string)
		exception(MALLOC, NULL, 1);
	mlx_string_put(scene->mlx, scene->win, 65, 20, COLOR_WHITE, string);
	free(string);
	string = ft_itoa(scene->camera_count);
	if (!string)
		exception(MALLOC, NULL, 1);
	mlx_string_put(scene->mlx, scene->win, 85, 20, COLOR_WHITE, string);
	free(string);
}

void	put_info_to_window(t_scene *scene)
{
	t_vector	direction;
	double 		data[6];

	direction = multiply_matrix_tuple(scene->view.rotate, &(scene->camera.orientation));
	mlx_string_put(scene->mlx, scene->win, 20, 20, COLOR_WHITE,
				   "Camera  /    x     y     z ");
	mlx_string_put(scene->mlx, scene->win, 20, 35, COLOR_WHITE, "center");
	mlx_string_put(scene->mlx, scene->win, 20, 50, COLOR_WHITE, "dir");
	data[0] = scene->camera.center.x;
	data[1] = scene->camera.center.y;
	data[2] = scene->camera.center.z;
	data[3] = direction.x;
	data[4] = direction.y;
	data[5] = direction.z;

	display_camera(scene, data, 105, 35);

	mlx_string_put(scene->mlx, scene->win, 20, scene->height - 35,
				   COLOR_WHITE, "Rotation :  arrows");
	mlx_string_put(scene->mlx, scene->win, 20, scene->height - 50,
				   COLOR_WHITE, "Zoom :  mouse wheel");
	mlx_string_put(scene->mlx, scene->win, 20, scene->height - 20,
				   COLOR_WHITE, "Resize objects :  mouse buttons");
}