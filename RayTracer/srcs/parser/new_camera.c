#include "minirt.h"

int	new_node_cam(t_camera **l_cameras, t_camera **new, int camera_count)
{
	t_camera	*ptr;

	*new = malloc(sizeof(t_camera));
	if (!*new)
		return (ERROR);
	(*new)->ident = C;
	(*new)->number = camera_count;
	if (!*l_cameras)
		*l_cameras = (*new);
	else
	{
		ptr = *l_cameras;
		while (ptr->number != camera_count - 1)
			ptr = ptr->next;
		ptr->next = (*new);
	}
	(*new)->next = *l_cameras;
	return (SUCCESS);
}

void	new_camera(t_camera **cameras, const char *line, int *camera_count)
{
	t_camera	*new;
	int			i;

	i = 0;
//	if (!new->ident)
//		cameras->ident = C;
//	else
//		exception(REPEAT_VAL, "Camera", 1);
	(*camera_count)++;
	if (!new_node_cam(cameras, &new, *camera_count))
		exception(MALLOC, NULL, 1);

	if (!get_tuple(line, &(new->center), &i, POINT) \
	|| !get_tuple(line, &(new->orientation), &i, VECTOR))
		exception(INVALID_VECTOR, line, 1);

	if (!ft_equal(module_v(&(new->orientation)), 1))
		exception(INVALID_VECTOR, line, 1);
	normalize(&(new->orientation));

	if (!get_digit(line, &(new->view_degree), &i, ' ') \
	|| new->view_degree < 0 || new->view_degree > 180)
		exception(INVALID_PARAMETER, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);
}
