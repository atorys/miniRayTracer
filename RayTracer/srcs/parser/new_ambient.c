#include "minirt.h"

void	new_ambient(t_ambient *a_light, const char *line)
{
	int	i;

	i = 0;
	if (!a_light->ident)
		a_light->ident = A;
	else
		exception(REPEAT_VAL, "Ambient light", 1);

	if (!get_digit(line, &(a_light->ratio), &i, 3) \
	|| a_light->ratio < 0 || a_light->ratio > 1)
		exception(INVALID_PARAMETER, line, 1);

	if (!get_tuple(line, &(a_light->color), &i, COLOR))
		exception(INVALID_COLOR, line, 1);

	if (!ft_isempty(&(line[i])))
		exception(UNDEFINED_PARAMETER, line, 1);
}
