/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:29:39 by faraz             #+#    #+#             */
/*   Updated: 2022/01/31 11:58:07 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	startindex(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0' && s1[i] != set[j])
			j++;
		if (set[j] == '\0')
			break ;
		i++;
	}
	return (i);
}

static int	endindex(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j] != '\0' && s1[i] != set[j])
			j++;
		if (set[j] == '\0')
			break ;
		i--;
	}
	return (i);
}

static int	strtrimlen(char const *s1, char const *set)
{
	int	diff;

	diff = endindex(s1, set) - startindex(s1, set);
	if (diff < 0)
		return (0);
	return (diff + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*result;
	int		len;
	int		start_index;

	if (!s1 || !set)
		return (0);
	len = strtrimlen(s1, set);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result)
	{
		start_index = startindex(s1, set);
		i = 0;
		while (i < len)
		{
			result[i] = s1[start_index + i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
