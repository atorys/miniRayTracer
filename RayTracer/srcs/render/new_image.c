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

t_ray	trace_ray(t_point *origin, int x, int y, t_view *view)
{
	t_ray 		ray;
	t_point		position;
	t_vector	direction;

	position = new_tuple(x * view->x_change,
						 y * view->y_change,
						 origin->z - 1, POINT);
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
//	mlx_string_put(scene->mlx, scene->win, scene->width / 2 - 30, 40, 999999999, "minirt");
	mlx_destroy_image(scene->mlx, scene->canvas.img);
	return (SUCCESS);
}
