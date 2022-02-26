/****************************************************************************
 *			Рендеринг сцены с учетом нового положения камеры				*
 *			Создание нового холста, отрисовка сцены и вывод 				*
 *			изображения в окно просмотра на экране							*
 ****************************************************************************/

#include "render.h"

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void	display_camera(t_scene *scene, double *data, int x, int y)
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
				   "Camera   /     x      y      z ");
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

t_ray	trace_ray(t_point *origin, int x, int y, t_view *view)
{
	t_ray 		ray;
	t_point		position;
	t_vector	direction;

	position = new_tuple(x * view->x_change,
						 y * view->y_change,
						  origin->z - 1, POINT);
//	position = multiply_matrix_tuple(view->transform, &position);
//	position = multiply_matrix_tuple(view->rotate, &position);
//	position.x += origin->x;
//	position.y += origin->y;
//	position.z += origin->z;
	direction = subtract(&position, origin);
	direction = multiply_matrix_tuple(view->transform, &direction);
	direction = multiply_matrix_tuple(view->rotate, &direction);
	normalize(&direction);
	ray = new_ray(origin, &direction);
	return (ray);
}

void	put_scene_on_canvas(t_scene *scene)
{
	t_ray		ray;
	int			x;
	int			y;
	int			half_w;
	int			half_h;

	half_w = scene->width / 2;
	half_h = scene->height / 2;
	y = half_h + 1;
	while (--y > -(half_h))
	{
		x = -(half_w) - 1;
		while (++x < half_w)
		{
			ray = trace_ray(&(scene->camera.center), x, y, &(scene->view));
			put_pixel(&(scene->canvas), \
					(int)ft_module(x + half_w), \
					(int)ft_module(y - half_h), \
					ft_convert_rgb_int(new_color(scene, &ray, 3)));
		}
	}
}

int	new_image(t_scene *scene)
{
	scene->canvas.img = mlx_new_image(scene->mlx, scene->width, scene->height);
	if (!scene->canvas.img)
		return (ERROR);
	scene->canvas.addr = mlx_get_data_addr(scene->canvas.img,\
											&scene->canvas.bpp,\
											&scene->canvas.length,\
											&scene->canvas.end);
	if (!scene->canvas.addr)
		return (ERROR);
	put_scene_on_canvas(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->canvas.img, 0, 0);
	if (scene->width > 400)
		put_info_to_window(scene);
	mlx_destroy_image(scene->mlx, scene->canvas.img);
	return (SUCCESS);
}
