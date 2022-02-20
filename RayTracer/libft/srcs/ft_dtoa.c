//
// Created by atory on 18.02.2022.
//

#include "../includes/libft.h"

char	*calc_string(int integer, int mantissa)
{
	char 	*itoa;
	char 	*result;
	char 	*tmp;

	result = ft_itoa(integer);
	if (!result)
		return (NULL);
	tmp = result;
	result = ft_strjoin(result, ".");
	if (!result)
		return (NULL);
	free(tmp);
	tmp = result;
	itoa = ft_itoa(mantissa);
	if (!itoa)
		return (NULL);
	result = ft_strjoin(result, itoa);
	if (!result)
		return (NULL);
	free(tmp);
	free(itoa);
	return (result);
}

char	*ft_dtoa(double n, int precision)
{
	char	*str;
	char 	*digit;
	char 	*tmp;

	str = NULL;
	if (n < 0)
	{
		str = ft_strdup("-");
		if (!str)
			return (NULL);
		n *= -1;
	}
	tmp = str;
	digit = calc_string((int)n,  (int)(n * precision) % precision);
	if (!digit)
		return (NULL);
	str = ft_strjoin(str, digit);
	if (!str)
		return (NULL);
	if (tmp)
		free(tmp);
	free(digit);
	return (str);
}
