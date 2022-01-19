/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:16:20 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n, int flag_len)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = -1;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while ((ss1[++i] != '\0' || ss2[i] != '\0') && n-- > 0)
	{
		if (ss1[i] != ss2[i])
		{
			if (ss1[i] > ss2[i])
				return (1);
			return (-1);
		}
	}
    if (flag_len && n > 0)
    {
        return (1);
    }
	return (0);
}
