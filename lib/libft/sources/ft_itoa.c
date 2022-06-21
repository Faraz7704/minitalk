/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 20:08:10 by faraz             #+#    #+#             */
/*   Updated: 2022/01/31 13:22:17 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digitlen(int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		len;
	char		*result;

	len = digitlen(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = '\0';
	if (n == -2147483648)
		return (ft_memcpy(result, "-2147483648", 11));
	if (n < 0)
	{
		n *= -1;
		result[0] = '-';
	}
	i = len - 1;
	if (n == 0)
		result[i] = '0';
	while (n > 0)
	{
		result[i--] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
