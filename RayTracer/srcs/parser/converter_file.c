#include "get_next_line.h"
#include "minirt.h"
#include "fcntl.h"

/*
 *                       ,->COLORS
 * PARSING : FILE->OBJECT->PARAMETERS->SUCCESS
 *                       `->VECTORS
 */

int	get_object(const char *line, t_scene *scene)
{
	int	i;
	int	i_space;

	i = 0;
	ft_skip_whitespace(line, &i);
	i_space = ft_next_whitespace(line, i);
	if (!ft_strncmp(&(line[i]), "C", (int)ft_max(i_space - i, 1), 0))
		new_camera(&(scene->camera), &(line[i_space]));
	else if (!ft_strncmp(&(line[i]), "A", (int)ft_max(i_space - i, 1), 0))
		new_ambient(&(scene->a_light), &(line[i_space]));
	else if (!ft_strncmp(&(line[i]), "L", (int)ft_max(i_space - i, 1), 0))
		new_light(&(scene->l_lights), &(line[i_space]));
	else if (!ft_strncmp(&(line[i]), "sp", (int)ft_max(i_space - i, 2), 0))
		new_sphere(&(scene->object), &(line[i_space]));
	else if (!ft_strncmp(&(line[i]), "cy", (int)ft_max(i_space - i, 2), 0))
		new_cylinder(&(scene->object), &(line[i_space]));
	else if (!ft_strncmp(&(line[i]), "pl", (int)ft_max(i_space - i, 2), 0))
		new_plane(&(scene->object), &(line[i_space]));
	else if (!ft_strncmp(&(line[i]), "#", (int)ft_max(i_space - i, 1), 0))
		return (SUCCESS);
	else
		return (exception(BAD_IDENT, (char *)&(line[i]), 0));
	return (SUCCESS);
}

int	convert_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	int		res;

	line = ft_strrchr(filename, '.');
	if (!line || ft_strncmp(line, ".rt", ft_max(ft_strlen(line), 3), 1) != 0)
		exception(EXTENSION, filename, 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exception(NO_FILE, filename, 1);
	line = NULL;
	res = 1;
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		if (!ft_isempty(line))
			if (!get_object(line, scene))
				return (ERROR);
		free(line);
	}
	close(fd);
	return (SUCCESS);
}
