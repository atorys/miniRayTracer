#include "minirt.h"

void	new_camera(t_camera *camera, const char *line)
{
	int	i;

	i = 0;
	if (!camera->object.ident)
		camera->object.ident = C;
	else
		exception(REPEAT_VAL, "Camera", 1);
	if (!get_tuple(line, &(camera->object.center), &i, POINT) \
	|| !get_tuple(line, &(camera->orientation), &i, VECTOR))
		exception(INVALID_VECTOR, line, 1);
	if (module_v(&camera->orientation) != 1) // todo : each should be -1;1
		exception(INVALID_VECTOR, line, 1);

	if (!get_digit(line, &(camera->view_degree), &i, 3) \
	|| camera->view_degree < 0 || camera->view_degree > 180)
		exception(INVALID_PARAMETER, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	camera->object.print_func = print_camera;
	camera->object.intersection_func = NULL;
}
