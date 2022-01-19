/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:15:08 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
    unsigned char	*arr1;
    unsigned char	*arr2;
    size_t			i;

    i = 0;
    arr1 = (unsigned char *)s1;
    arr2 = (unsigned char *)s2;
    while (i < n)
    {
        if (arr1[i] != arr2[i])
        {
            return (arr1[i] - arr2[i]);
        }
        i++;
    }
    return (0);
}
