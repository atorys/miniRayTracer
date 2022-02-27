#include "minirt.h"
#include "render.h"

void	new_ambient(t_ambient *new, const char *line)
{
	int	i;

	i = 0;
	if (!new->ident)
		new->ident = A;
	else
		exception(REPEAT_VAL, "Ambient light", 1);

	if (!get_digit(line, &(new->ratio), &i, ' ') \
	|| new->ratio < 0 || new->ratio > 1)
		exception(INVALID_PARAMETER, line, 1);

	if (!get_tuple(line, &(new->effective_color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	/*
	 * additional calculation for optimization
	 */
	new->effective_color = ft_color_multiplication(&(new->effective_color),
													   new->ratio);
}
