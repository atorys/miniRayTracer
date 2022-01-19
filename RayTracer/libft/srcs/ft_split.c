/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:15:34 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static unsigned int	ft_strcount(char const *s, char c)
{
	unsigned int	count;
	int				i;
	int				k;

	count = 0;
	i = 0;
	if (!ft_strchr(s, c))
		return (1);
	while (s[i])
	{
		k = 0;
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i + k] != '\0' && s[i + k] != c)
			k++;
		if (k > 0)
			count++;
		i += k;
	}
	return (count);
}

static char	*ft_free(char **array)
{
	while (*array)
	{
		free(*array);
		array++;
	}
	free(array);
	return (NULL);
}

static char	*writeln(char **array, char const *s, size_t k, unsigned int j)
{
	char	*line;

	line = ft_substr(s, j, k);
	if (!line)
		return (ft_free(array));
	return (line);
}

char	**ft_split(char const *s, char c)
{
	char			**array;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	array = (char **)malloc(sizeof(char *) * (ft_strcount(s, c) + 1));
	if (!array)
		return (NULL);
	i = -1;
	j = 0;
	while (s[j] && ++i < ft_strcount(s, c))
	{
		k = 0;
		while (s[j] != '\0' && s[j] == c)
			j++;
		while (s[j + k] != '\0' && s[j + k] != c)
			k++;
		array[i] = writeln(array, s, (size_t)k, j);
		if (!array[i])
			return (NULL);
		j += k;
	}
	array[i] = NULL;
	return (array);
}
