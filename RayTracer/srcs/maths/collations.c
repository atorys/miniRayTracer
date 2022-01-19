/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:51:44 by atory             #+#    #+#             */
/*   Updated: 2021/12/05 07:59:53 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	ft_max_module(double a, double b)
{
	if (a * (double)(1 - (2 * (a < 0))) > b * (double)(1 - (2 * (b < 0))))
		return (a * (double)(1 - (2 * (a < 0))));
	else
		return (b * (double)(1 - (2 * (b < 0))));
}

double	ft_min_module(double a, double b)
{
	if (a * (double)(1 - (2 * (a < 0))) < b * (double)(1 - (2 * (b < 0))))
		return (a * (double)(1 - (2 * (a < 0))));
	else
		return (b * (double)(1 - (2 * (b < 0))));
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_module(double a)
{
	if (a < 0)
		return (-1 * a);
	return (a);
}
