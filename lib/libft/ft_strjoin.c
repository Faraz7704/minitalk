/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:59:26 by faraz             #+#    #+#             */
/*   Updated: 2022/01/07 17:28:33 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		s1_size;
	int		total_size;

	if (!s1 || !s2)
		return (0);
	s1_size = ft_strlen(s1);
	total_size = s1_size + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * total_size);
	if (result)
	{
		ft_strlcpy(result, s1, s1_size + 1);
		ft_strlcat(result, s2, total_size);
	}	
	return (result);
}
