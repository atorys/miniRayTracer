#include "minirt.h"

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_convert_rgb_int(t_color color)
{
	return (((int)color.x << 16 | (int)color.y << 8 | (int)color.z));
}

int hit(t_scene *scene, t_ray *ray)
{
	t_object	*object;
	t_object	*closest_object;
	double		min_distance;

	closest_object = NULL;
	object = scene->object;
	min_distance = MAX_DOUBLE;
	while (object)
	{
		t_pair t = intersect(object, ray);
		if (t.x < min_distance && t.x != MAX_DOUBLE && t.x > 0) {
			min_distance = t.x;
			closest_object = object;
		}
		object = object->next;
	}
	if (closest_object)
		return (lightning(scene, closest_object, ray, min_distance));
	return (0);
}

void	ray_tracing(t_scene *scene)
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
			t_point position = new_tuple(x * scene->view.x_change,
										 y * scene->view.y_change,
										 scene->camera.object.center.z - 1, POINT);
			t_vector direction = subtract(&position, &(scene->camera.object.center));
			direction = multiply_matrix_tuple(scene->view.rotation, &direction);
			normalize(&direction);
			ray = new_ray(&(scene->camera.object.center), &direction);
			put_pixel(&(scene->canvas), \
									(int)ft_module(x + half_w), \
									(int)ft_module(y - half_h), \
										hit(scene, &ray));
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
	ray_tracing(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->canvas.img, 0, 0);
//	mlx_string_put(rt->mlx, rt->win, rt->width / 2 - 30, 40, 1999999999, "minirt");
	mlx_destroy_image(scene->mlx, scene->canvas.img);
	return (SUCCESS);
}
