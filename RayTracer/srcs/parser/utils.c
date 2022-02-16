/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:51:44 by atory             #+#    #+#             */
/*   Updated: 2021/12/05 07:59:40 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_skip_whitespace(const char *str, int *i)
{
	if (!str[*i])
		return ;
	while (str[*i] && (str[*i] == ' ' \
		|| str[*i] == '\t' \
		|| str[*i] == '\n' \
		|| str[*i] == '\r' \
		|| str[*i] == '\v' \
		|| str[*i] == '\f'))
		(*i)++;
}

int	ft_next_whitespace(const char *str, int i)
{
	if (!str)
		return (i);
	while (str[i] \
		&& str[i] != ' ' \
		&& str[i] != '\t'\
		&& str[i] != '\n'\
		&& str[i] != '\r'\
		&& str[i] != '\v'\
		&& str[i] != '\f')
		i++;
	return (i);
}

int	check_digit(char *digit)
{
	int	start;
	int	end;
	int	dots_count;

	if (!digit || ft_isempty(digit))
		return (ERROR);
	start = 0;
	dots_count = 0;
	ft_skip_whitespace(digit, &start);
	end = ft_next_whitespace(digit, start);
	while (start < end)
	{
		if (!ft_isdigit(digit[start]) && digit[start] != '.' \
		&& digit[start] != '-')
			return (ERROR);
		if (digit[start] == '.')
			dots_count++;
		start++;
	}
	ft_skip_whitespace(digit, &start);
	if (digit[start] || dots_count > 1)
		return (ERROR);
	return (SUCCESS);
}

int	get_digit(const char *line, double *container, int *i, char split_char)
{
	char	*digit;
	char	*digit_tmp;
	char	*comma;

	ft_skip_whitespace(line, i);
	if (line[*i] == ',')
		*i += 1;
	ft_skip_whitespace(line, i);
	comma = ft_strchr(&(line[*i]), split_char);
	if (comma == NULL)
		comma = (char *)&(line[ft_strlen(line)]);
	digit = ft_substr(line, *i, ft_sigmlen(&(line[*i]), comma));
	if (!digit || !check_digit(digit))
		return (ERROR);
	*i += ft_sigmlen(&(line[*i]), comma);
	digit_tmp = digit;
	digit = ft_strtrim(digit, " \t\n\v\r\f");
	if (!digit)
		return (ERROR);
	free(digit_tmp);
	*container = ft_atod(digit);
	free(digit);
	return (SUCCESS);
}

int	get_tuple(const char *line, t_tuple *tuple, int *i, double type)
{
	if (!get_digit(line, &(tuple->x), i, ',') \
	|| !get_digit(line, &(tuple->y), i, ',') \
	|| !get_digit(line, &(tuple->z), i, ' '))
		return (ERROR);
	tuple->w = type;
	if (type == COLOR && (tuple->x < 0 || tuple->x > 255 \
		|| tuple->y < 0 || tuple->y > 255 \
		|| tuple->z < 0 || tuple->z > 255))
		return (ERROR);
	return (SUCCESS);
}
