//
// Created by atory on 19.01.2022.
//

#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "objects.h"
# include "matrix.h"

# ifdef	LINUX
#	define MLX_LIBRARY "../mlx/mlx_linux/mlx.h"
# else
#	define MLX_LIBRARY "../mlx/mlx_mac/mlx.h"
# endif

# include MLX_LIBRARY

# define WIN_HEIGHT	1080
# define WIN_WIDTH	1920
//# define WIN_HEIGHT	400
//# define WIN_WIDTH	400
//# define WIN_HEIGHT	800
//# define WIN_WIDTH	800
# define SUCCESS	1
# define ERROR		0

typedef struct s_scene_attributes	t_scene;
typedef struct s_image				t_image;
typedef struct s_view				t_view;


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

	t_matrix*	transform;
	t_matrix*	rotate;
};

struct s_scene_attributes
{
	void		*mlx;
	void		*win;

	int			width;
	int			height;

	t_image		canvas;
	t_view		view;

	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_object 	*object;
};

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
int		get_digit(const char *line, double *container, int *i, char split_char);

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
 * VIEW.C
 */
int			calculate_view_reference(t_scene *scene);
t_matrix	*transform_view(t_point *from, t_vector *forward, t_vector up);

/*
* EXCEPTION.C
*/
int		exception(const char *message, const char *error_line, int code);

# define DEF_COLOR           "\033[1;31m"
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


#endif
