#include "minirt.h"

void	new_camera(t_camera *camera, const char *line)
{
	int	i;

	i = 0;
	if (!camera->ident)
		camera->ident = C;
	else
		exception(REPEAT_VAL, "Camera", 1);
	if (!get_tuple(line, &(camera->center), &i, POINT) \
	|| !get_tuple(line, &(camera->orientation), &i, VECTOR))
		exception(INVALID_VECTOR, line, 1);

	if (!ft_equal(module_v(&(camera->orientation)), 1))
		exception(INVALID_VECTOR, line, 1);
	normalize(&(camera->orientation));

	if (!get_digit(line, &(camera->view_degree), &i, ' ') \
	|| camera->view_degree < 0 || camera->view_degree > 180)
		exception(INVALID_PARAMETER, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);
}
