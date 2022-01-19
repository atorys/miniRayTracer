/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:14:46 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_isempty(const char *str)
{
    int i;

    i = -1;
    if (ft_strlen(str) == 0)
        return (1);
    while (str[++i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
    }
    return (1);
}