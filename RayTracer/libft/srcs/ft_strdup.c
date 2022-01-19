/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:15:50 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*cpy;

	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!cpy)
		return (NULL);
	i = -1;
	while (str[++i])
		cpy[i] = (char)str[i];
	cpy[i] = '\0';
	return (cpy);
}
