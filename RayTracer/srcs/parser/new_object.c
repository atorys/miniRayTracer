//
// Created by atory on 19.01.2022.
//

#include "minirt.h"

int	add_object(t_object **object, t_object *new)
{
	t_object	*ptr;

	new->next = NULL;
	if (!*object)
		*object = new;
	else
	{
		ptr = *object;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (SUCCESS);
}

void	new_sphere(t_object **object, const char *line)
{
	int			i;
	t_sphere	*new;

	i = 0;
	new = malloc(sizeof(t_sphere));
	if (!new)
		exception(MALLOC, NULL, 1);
	add_object(object, ((t_object *)new));
	new->object.ident = sp;

	if (!get_tuple(line, &(new->object.center), &i, POINT))
		exception(INVALID_VECTOR, line, 1);

	if (!get_digit(line, &(new->diameter), &i, 3) || new->diameter < 0)
		exception(INVALID_PARAMETER, line, 1);

	if (!get_tuple(line, &(new->object.color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	new->object.print_func = print_sphere;
	new->object.intersection_func = intersect_sp;
}

void    new_plane(t_object **object, const char *line)
{
	int         i;
	t_plane     *new;

	i = 0;
	new = malloc(sizeof(t_plane));
	if (!new)
		exception(MALLOC, NULL, 1);
	add_object(object, ((t_object *)new));
	new->object.ident = pl;

	if (!get_tuple(line, &(new->object.center), &i, POINT) \
    || !get_tuple(line, &(new->orientation), &i, VECTOR))
		exception(INVALID_VECTOR, line, 1);

	if (module_v(&new->orientation) != 1) // todo : each should be -1;1
		exception(INVALID_VECTOR, line, 1);

	if (!get_tuple(line, &(new->object.color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	new->object.print_func = print_plane;
	new->object.intersection_func = NULL;
}

void	new_cylinder(t_object **object, const char *line)
{
	int			i;
	t_cylinder	*new;

	i = 0;
	new = malloc(sizeof(t_cylinder));
	if (!new)
		exception(MALLOC, NULL, 1);
	add_object(object, ((t_object *)new));
	new->object.ident = cy;

	if (!get_tuple(line, &(new->object.center), &i, POINT) \
	|| !get_tuple(line, &(new->orientation), &i, VECTOR))
		exception(INVALID_VECTOR, line, 1);

	if (module_v(&new->orientation) != 1) // todo : each should be -1;1
		exception(INVALID_VECTOR, line, 1);

	if (!get_digit(line, &(new->diameter), &i, 3) || new->diameter < 0)
		exception(INVALID_PARAMETER, line, 1);
	if (!get_digit(line, &(new->height), &i, 3) || new->height < 0)
		exception(INVALID_PARAMETER, line, 1);

	if (!get_tuple(line, &(new->object.color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	new->object.print_func = print_cylinder;
	new->object.intersection_func = NULL;
}
