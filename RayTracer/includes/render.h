//
// Created by atory on 17.02.2022.
//

#ifndef RENDER_H
# define RENDER_H

# include "ray.h"
# include "minirt.h"

# define COLOR_WHITE 16777215

typedef struct s_hit			t_hit;
typedef struct s_computations	t_comp;

struct	s_hit
{
	t_object	*object;
	t_pair		pair;
};

struct s_computations
{
	t_ray		*ray;
	t_object	*object;
	double		t1;
	double		t2;
	t_point		point;
	t_point		over_point;
	t_vector	eye_v;
	t_vector	reflect_v;
	t_vector 	normal;
	bool		inside;
	double 		m_param1;
	double 		m_param2;
};

/*
 * NEW_IMAGE.C
 */
int			new_image(t_scene *scene);
t_ray		trace_ray(t_point *origin, int x, int y, t_view *view);
t_color		lightning(t_scene *scene, t_comp *computations);

/*
 * COMPUTATIONS.C
 */
t_hit		new_hit(t_scene *scene, t_ray *ray);
void		prepare_computations(t_comp *computations,
								 t_scene *scene,
								 t_ray *ray);
double		closest_point_on_cylinder_axis(t_cylinder *cylinder,
											 t_ray *ray,
											 double t1,
											 double t2);

/*
 * COLOR.C
 */
t_color		new_color(t_scene *scene, t_ray *ray, int recursion_depth);
int			ft_convert_rgb_int(t_color color);
t_color		ft_color_multiplication(t_color *color_1,
									   double scalar);
t_color		ft_color_addition(t_color *color_1,
								 t_color *color_2);

#endif
