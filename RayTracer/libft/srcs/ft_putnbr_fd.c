/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:38:45 by atory             #+#    #+#             */
/*   Updated: 2021/05/01 23:56:45 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	char 		number[30];
	long		temp_nbr;
	size_t		length;
	int			i;

	if (nbr < 0)
		write(fd, "-", 1);
	nbr = 1 - (2 * (nbr < 0));
	length = 0;
	temp_nbr = nbr;
	if (temp_nbr == 0)
		length++;
	while (temp_nbr != 0 && ++length)
		temp_nbr /= 10;
	if (nbr == 0 && ++length)
		number[0] = '0';
	i = -1;
	while (++i < length && nbr > 0)
	{
		number[i] = (char)(nbr % 10 + '0');
		nbr /= 10;
	}
	write(fd, number, length);
}
