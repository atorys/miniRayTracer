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

t_color	new_color(t_scene *scene, t_ray *ray, int recursion_depth)
{
	t_hit	h;
	t_color	color;

	h = hit(scene, ray);
	if (!h.object)
		return ((t_color){0, 0, 0, COLOR});
	color = lightning(scene, h.object, ray, h.pair.x);
	if (recursion_depth <= 0 || h.object->reflective < 0)
		return (color);

	t_point point = ray_position(ray, h.pair.x);
//	t_vector minus_d = multiply_on_scalar(ray->direction, -1);
//	t_vector minus_d = subtract(&(scene->camera.center), &point);
//	normalize(&minus_d);
	t_vector normal = normal_at(h.object, &point);
	t_vector reflected = reflect(ray->direction, &normal);
	normalize(&reflected);
	t_ray reflected_ray = new_ray(&point, &reflected);
	t_color reflected_color = new_color(scene, &reflected_ray, recursion_depth - 1);
	color = ft_color_multiplication(&color, 1 - h.object->reflective);
	reflected_color = ft_color_multiplication(&color, h.object->reflective);

	return (ft_color_addition(&color, &reflected_color));
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
										ft_convert_rgb_int(new_color(scene, &ray, 2)));
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
