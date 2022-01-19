/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:14:27 by atory             #+#    #+#             */
/*   Updated: 2021/11/29 22:17:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long long	ft_atoi(const char *str)
{
	long long	digit;
	int			flag;

	digit = 0;
	flag = 1;
	while (*str == ' ' || *str == '\v' || *str == '\t' ||\
	 *str == '\f' || *str == '\r' || *str == '\n')
		str++;
	if (*str == '-' && str++)
		flag = -1;
	while (*str >= '0' && *str <= '9' && *str)
		digit = (digit * 10) + (*str++ - '0');
	return (flag * digit);
}
