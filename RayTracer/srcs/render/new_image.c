/****************************************************************************
 *			Рендеринг сцены с учетом нового положения камеры				*
 *			Создание нового холста, отрисовка сцены и вывод 				*
 *			изображения в окно просмотра на экране							*
 ****************************************************************************/

#include "render.h"
#include "pthread.h"
#define	TH WIN_HEIGHT

typedef struct s_av
{
	int		id;
	t_scene	*scene;
}	t_av;

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->length + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

t_ray	trace_ray(t_point *origin, int x, int y, t_view *view)
{
	t_ray 		ray;
	t_vector	position;

	position = new_tuple(x * view->x_change,
						 y * view->y_change,
						  - 1, VECTOR);
	position = multiply_matrix_tuple(view->transform, &position);
	position = multiply_matrix_tuple(view->rotate, &position);
	normalize(&position);
	ray = new_ray(origin, &position);
	return (ray);
}

/**
 * RAY TRACING WITH THREADS
 */
void	*put_scene_on_canvas(void *avv)
{
	t_av		av;
	t_ray		ray;
	int			x;
	int			y;
	int			half_w;
	int			half_h;

	av = *((t_av *)avv);
	half_w = av.scene->width / 2;
	half_h = av.scene->height / 2;

	y = half_h - av.scene->height / TH * av.id + 1;

	while (--y > half_h - (av.scene->height / TH * (av.id + 1)))
	{
		x = -half_w - 1;
		while (++x < half_w)
		{
			ray = trace_ray(&(av.scene->camera.center), x, y, &(av.scene->view));
			put_pixel(&(av.scene->canvas),
					(int)ft_module(x + half_w),
					(int)ft_module(y - half_h),
					ft_convert_rgb_int(new_color(av.scene, &ray, 3)));
		}
	}
	return (NULL);
}

/**
 * RAY TRACING WITHOUT THREADS
 */
//void	put_scene_on_canvas(t_scene *scene)
//{
//	t_ray		ray;
//	int			x;
//	int			y;
//	int			half_w;
//	int			half_h;
//
//	half_w = scene->width / 2;
//	half_h = scene->height / 2;
//	y = half_h + 1;
//	while (--y > -(half_h))
//	{
//		x = -(half_w) - 1;
//		while (++x < half_w)
//		{
//			ray = trace_ray(&(scene->camera.center), x, y, &(scene->view));
//			put_pixel(&(scene->canvas), \
//					(int)ft_module(x + half_w), \
//					(int)ft_module(y - half_h), \
//					ft_convert_rgb_int(new_color(scene, &ray, 3)));
//		}
//	}
//}

void	run_threads(t_scene *scene)
{
	pthread_t	threads[TH];
	t_av		av[TH];
	int			count;

	count = -1;
	while (++count < TH)
	{
		av[count].id = count;
		av[count].scene = scene;
		if (pthread_create(&(threads[count]), NULL, put_scene_on_canvas, &(av[count])))
			exception("pthread_create()", NULL, 1);
	}
	count = -1;
	while (++count < TH)
		if (pthread_join(threads[count], NULL) != 0)
			exception("pthread_join()", NULL, 1);
}

int	new_image(t_scene *scene)
{
	scene->canvas.img = mlx_new_image(scene->mlx, scene->width, scene->height);
	if (!scene->canvas.img)
		return (ERROR);
	scene->canvas.addr = mlx_get_data_addr(scene->canvas.img,
											&scene->canvas.bpp,
											&scene->canvas.length,
											&scene->canvas.end);
	if (!scene->canvas.addr)
		return (ERROR);

	run_threads(scene);

	mlx_put_image_to_window(scene->mlx, scene->win, scene->canvas.img, 0, 0);
	if (scene->width > 400)
		put_info_to_window(scene);
	mlx_destroy_image(scene->mlx, scene->canvas.img);
	return (SUCCESS);
}
