/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:14:10 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static double  pow(double num, double n)
{
    double num_n;

    num_n = 1;
    while (n > 0 && n--)
        num_n *= num;
    while (n < 0 && n++)
        num_n /= num;
    return (num_n);
}

double  ft_atod(const char *str)
{
    double  digit;
    int     flag;
    int     n;

    digit = 0;
    flag = 1;
    while (*str == ' ' || *str == '\v' || *str == '\t' ||\
	 *str == '\f' || *str == '\r' || *str == '\n')
        str++;
    if (*str == '-' && str++)
        flag = -1;
    while (*str == '-' || *str == '+')
        str++;
    while (*str >= '0' && *str <= '9' && *str)
        digit = (digit * 10) + (*str++ - '0');
    if (*str && *str == '.')
    {
        str++;
        n = -1;
        while (*str >= '0' && *str <= '9' && *str)
            digit += (*str++ - '0') * pow(10, n--);
    }
    return (flag * digit);
}
