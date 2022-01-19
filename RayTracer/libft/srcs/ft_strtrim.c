/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:46:17 by atory             #+#    #+#             */
/*   Updated: 2021/04/29 18:10:03 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_left(char const *s1, char const *set)
{
	int	delete;
	int	flag;
	int	i;
	int	j;

	delete = 0;
	flag = -1;
	i = 0;
	j = 0;
	while (s1[i] != '\0' && flag != 0)
	{
		flag = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				flag++;
			j++;
		}
		if (flag != 0)
			delete++;
		i++;
	}
	return (delete);
}

static int	ft_right(char const *s1, char const *set)
{
	int	delete;
	int	flag;
	int	i;
	int	j;

	delete = 0;
	flag = -1;
	i = ft_strlen(s1) - 1;
	j = 0;
	while (i > 0 && flag != 0)
	{
		flag = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				flag++;
			j++;
		}
		if (flag != 0)
			delete++;
		i--;
	}
	return (delete);
}

static char	*ft_trimmed(char *cpy, char const *s1, char const *set,
	int strcount)
{
	int	k;
	int	index;

	k = 0;
	index = ft_left(s1, set);
	while (strcount > 0)
	{
		cpy[k] = s1[index];
		index++;
		strcount--;
		k++;
	}
	if (k == 0)
	{
		return (cpy);
	}
	cpy[k] = '\0';
	return (cpy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	int		strcount;

	if (!s1 || !set)
		return (NULL);
	strcount = ft_strlen(s1) - (ft_left(s1, set) + ft_right(s1, set));
	if (strcount <= 0)
	{
		cpy = ft_calloc(sizeof(char), 1);
		if (!cpy)
			return (NULL);
		return (cpy);
	}
	cpy = malloc(sizeof(char) * (strcount + 1));
	if (cpy)
	{
		cpy = ft_trimmed(cpy, s1, set, strcount);
		return (cpy);
	}
	return (NULL);
}
