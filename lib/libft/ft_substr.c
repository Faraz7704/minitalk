/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:35:34 by faraz             #+#    #+#             */
/*   Updated: 2022/01/09 19:19:39 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	size_t	msize;
	char	*result;

	if (!s)
		return (0);
	msize = ft_strlen(&s[start]);
	if (len > msize)
		len = msize;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	size = ft_strlen(s);
	i = 0;
	while (i < len && start + i < size)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
