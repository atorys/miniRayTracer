#include "minirt.h"
#include "render.h"

int	new_node_l(t_light **l_light, t_light **new)
{
	t_light	*ptr;

	*new = malloc(sizeof(t_light));
	if (!*new)
		return (ERROR);
	(*new)->ident = L;
	(*new)->next = NULL;
	if (!*l_light)
		*l_light = (*new);
	else
	{
		ptr = *l_light;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = (*new);
	}
	return (SUCCESS);
}

void	new_light(t_light **l_light, const char *line)
{
	int		i;
	t_light	*new;

	i = 0;
	if (!new_node_l(l_light, &new))
		exception(MALLOC, NULL, 1);

	if (!get_tuple(line, &(new->center), &i, POINT))
		exception(INVALID_VECTOR, line, 1);

	if (!get_digit(line, &(new->bright), &i, 3) \
	|| new->bright < 0 || new->bright > 1)
		exception(INVALID_PARAMETER, line, 1);

	if (!get_tuple(line, &(new->color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	/*
	 * additional calculation for optimization
	 */
	new->effective_color =  ft_color_multiplication(&(new->color), new->bright);
}
