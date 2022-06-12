/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:29:50 by faraz             #+#    #+#             */
/*   Updated: 2022/01/07 14:58:24 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*result;

	len = ft_strlen(str) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (!result)
		return (0);
	ft_strlcpy(result, str, len);
	return (result);
}
