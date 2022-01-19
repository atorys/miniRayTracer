/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:16:51 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (len-- > 0 && s[start] != '\0' && start < ft_strlen(s))
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
