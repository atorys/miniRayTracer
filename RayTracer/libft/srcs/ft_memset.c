/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atory <atory@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:26:19 by atory             #+#    #+#             */
/*   Updated: 2021/04/27 18:10:30 by atory            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	char	*destcpy;

	destcpy = (char *)dest;
	while (len > 0)
	{
		*destcpy = (char)c;
		destcpy++;
		len--;
	}
	return (dest);
}
