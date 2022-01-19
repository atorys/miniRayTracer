/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:16:27 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
    size_t	i;
    char	*temp;

    temp = NULL;
    i = ft_strlen(s);
    if ((char)c == '\0' && s[ft_strlen(s)] == (char)c)
        return ((char *)s + i);
    while (*s)
    {
        if (*s == (char)c)
        {
            temp = (char *)s;
        }
        s++;
    }
    return (temp);
}