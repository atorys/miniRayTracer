#include "minirt.h"

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

t_hit	hit(t_scene *scene, t_ray *ray)
{
	t_hit		h;
	t_object	*object;
	double		min_distance;

	object = scene->object;
	min_distance = MAX_DOUBLE;
	h.object = NULL;
	while (object)
	{
		t_pair pair = intersect(object, ray);
		if (pair.x < min_distance && pair.x != MAX_DOUBLE && pair.x > 0) {
			min_distance = pair.x;
			h.object = object;
			h.pair = pair;
		}
		object = object->next;
	}
	return (h);
}

int	new_color(t_scene *scene, t_ray *ray)
{
	t_hit h;

	h = hit(scene, ray);
	if (h.object)
		return (lightning(scene, h.object, ray, h.pair.x));
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
										 scene->camera.center.z - 1, POINT);
			t_vector direction = subtract(&position, &(scene->camera.center));
			direction = multiply_matrix_tuple(scene->view.rotation, &direction);
			normalize(&direction);
			ray = new_ray(&(scene->camera.center), &direction);
			put_pixel(&(scene->canvas), \
									(int)ft_module(x + half_w), \
									(int)ft_module(y - half_h), \
										new_color(scene, &ray));
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
