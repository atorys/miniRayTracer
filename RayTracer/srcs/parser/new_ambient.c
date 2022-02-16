#include "minirt.h"
#include "render.h"

void	new_ambient(t_ambient *ambient, const char *line)
{
	int	i;

	i = 0;
	if (!ambient->ident)
		ambient->ident = A;
	else
		exception(REPEAT_VAL, "Ambient light", 1);

	if (!get_digit(line, &(ambient->ratio), &i, 3) \
	|| ambient->ratio < 0 || ambient->ratio > 1)
		exception(INVALID_PARAMETER, line, 1);

	if (!get_tuple(line, &(ambient->color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);

	/*
	 * additional calculation for optimization
	 */
	ambient->effective_color = ft_color_multiplication(&(ambient->color),
													   ambient->ratio);
}
