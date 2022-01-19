/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:15:57 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	unsigned int	i;

	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	result = malloc(sizeof(int) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (*s1)
		result[i++] = (char)*s1++;
	while (*s2)
		result[i++] = (char)*s2++;
	result[i] = '\0';
	return (result);
}
