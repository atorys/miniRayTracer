//
// Created by atory on 19.01.2022.
//

#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "tuple.h"
# include "matrix.h"
# include "objects.h"
# include "ray.h"

//# ifdef	LINUX
#	include "../mlx/mlx_linux/mlx.h"
//# elseif
//#	include "mlx.h"
//# endif

# define WIN_HEIGHT	1080
# define WIN_WIDTH	1920
# define SUCCESS	1
# define ERROR		0

typedef struct s_scene_attributes	t_scene;
typedef struct s_image				t_image;
typedef struct s_view				t_view;
typedef struct s_ray				t_ray;


struct s_image
{
	void	*img;
	char	*addr;

	int		bpp;
	int		length;
	int		end;

	int		h;
	int		w;
};

struct s_view
{
	double		width;
	double		height;

	double		x_change;
	double		y_change;

	double 		rotation_x;
	double 		rotation_y;
	double 		rotation_z;

	t_matrix*	rotation;
	t_matrix*	no_rotation;

//	t_vector	*camera_right;
//	t_vector	*camera_up;
//	t_vector	*camera_dir;
//	t_vector	*camera_pos;
};

struct s_scene_attributes
{
	void		*mlx;
	void		*win;

	int			width;
	int			height;

	t_image		canvas;
	t_view		view;

	t_ambient	a_light;
	t_camera	camera;
	t_light		*l_lights;
	t_object 	*object;
};

/*
 * EXCEPTION.C
 */
int		exception(const char *message, const char *error_line, int code);

# define DEF_COLOR               "\033[1;31m"
# define NO_COLOR            "\033[0m"

# define ARGUMENT            "too few arguments"
# define EXTENSION           "a scene must have extension *.rt"
# define NO_FILE             "file doesn't exist"
# define MALLOC              "malloc() failed"
# define MLX                 "mlx() failed"
# define BAD_IDENT           "invalid or empty identifier"
# define REPEAT_VAL          "can only be declared once"
# define NO_VAL				 "should be declared at least once"
# define INVALID_VECTOR      "invalid vector configuration"
# define INVALID_PARAMETER   "invalid numeric parameter configuration"
# define INVALID_COLOR       "invalid color configuration: RGB range [0-255]"
# define UNDEFINED_PARAMETER "unexpected parameter in line"

/*
 * INIT.C
 */
int		init_scene(t_scene *scene);
int		init_mlx(t_scene *scene);

/*
 * PARSER
 */
int		convert_file(const char *filename, t_scene *scene);

int		get_object(const char *line, t_scene *scene);
int		get_tuple(const char *line, t_tuple *tuple, int *i, double type);
int		get_digit(const char *line, double *container, int *i, int n);

void	new_camera(t_camera *camera, const char *line);
void	new_ambient(t_ambient *amb, const char *line);
void	new_light(t_light **l_light, const char *line);
void	new_sphere(t_object **object, const char *line);
void    new_plane(t_object **object, const char *line);
void    new_cylinder(t_object **object, const char *line);

int		check_digit(char *digit);
int		ft_next_whitespace(const char *str, int i);
void	ft_skip_whitespace(const char *str, int *i);


/*
 * RENDER
 */
typedef struct s_hit	t_hit;
struct	s_hit
{
	t_object	*object;
	t_pair		pair;
};

int			new_image(t_scene *scene);
t_color		new_color(t_scene *scene, t_ray *ray, int recursion_depth);
t_color		lightning(t_scene *scene,
						 t_object *object,
						 t_ray *ray,
						 double distance);
t_hit		hit(t_scene *scene, t_ray *ray);

/*
 * COLOR.C
 */
int			ft_convert_rgb_int(t_color color);
t_color		ft_color_multiplication(t_color *light_col,
									   double scalar);
t_color		ft_color_addition(t_color *light_col,
								 t_color *object_col);

#endif
