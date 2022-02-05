#include "minirt.h"

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

t_hit	new_hit(t_scene *scene, t_ray *ray)
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
		if (pair.x < min_distance && pair.x != MAX_DOUBLE && pair.x >= 0) {
			min_distance = pair.x;
			h.object = object;
			h.pair = pair;
		}
		object = object->next;
	}
	return (h);
}

void	prepare_computations(t_comp *computations, t_scene *scene, t_ray *ray)
{
	t_hit	hit;

	hit = new_hit(scene, ray);
	if (!hit.object)
	{
		computations->object = NULL;
		return ;
	}
	computations->ray = ray;
	computations->object = hit.object;
	computations->distance = hit.pair.x;
	computations->point = ray_position(ray, computations->distance);
	computations->eye_v = multiply_on_scalar(&(ray->direction), -1);
	computations->normal = normal_at(computations->object,
									&(computations->point));
	if (dot(&computations->normal, &computations->eye_v) < 0)
	{
		computations->inside = true;
		computations->normal = multiply_on_scalar(&(computations->normal), -1);
	}
	else
		computations->inside = false;
	computations->over_point = multiply_on_scalar(&(computations->normal), EPSILON);
	computations->over_point = add(&(computations->point), &(computations->over_point));
}

t_color	new_color(t_scene *scene, t_ray *ray, int recursion_depth)
{
	t_comp	computations;
	t_color	color;

	prepare_computations(&computations, scene, ray);
	if (!computations.object)
		return ((t_color){0, 0, 0, COLOR});
	color = lightning(scene, &computations);
	if (recursion_depth <= 0 || computations.object->reflective < 0)
		return (color);

	t_vector reflected = reflect(&(ray->direction), &(computations.normal));
	normalize(&reflected);
	t_ray reflected_ray = new_ray(&(computations.point), &reflected);
	t_color reflected_color = new_color(scene, &reflected_ray, recursion_depth - 1);
	reflected_color = ft_color_multiplication(&color, computations.object->reflective);
	color = ft_color_multiplication(&color, 1 - computations.object->reflective);

	return (ft_color_addition(&color, &reflected_color));
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
					ft_convert_rgb_int(new_color(scene, &ray, 0)));
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
