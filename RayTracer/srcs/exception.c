#include "minirt.h"

int	exception(const char *message, const char *error_line, int code)
{
	if (error_line)
	{
		write(2, DEF_COLOR, 7);
		write(2, error_line, ft_strlen(error_line));
		write(2, "\n", 1);
		write(2, NO_COLOR, 4);
	}
	if (message)
	{
		write(2, "Error: ", 7);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (!code)
		return (0);
	exit(code);
}
