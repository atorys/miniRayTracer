//
// Created by atory on 18.02.2022.
//

#include "../includes/libft.h"

char	*ft_dtoa(double n, int precision)
{
	char	*str;
	long	integer;
	long	mantissa;
	char 	*s1;
	char 	*s2;

	integer = (int)n;
	mantissa = (int)(n * precision) % precision;
	if (mantissa < 0)
		mantissa *= -1;
	s1 = ft_itoa(integer);
	s2 = ft_itoa(mantissa);
	if (!s1 || !s2)
		return (NULL);
	s1 = ft_strjoin(s1, ".");
	str = ft_strjoin(s1, s2);
	if (!str)
		return (NULL);
	return (str);
}
