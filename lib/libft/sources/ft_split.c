/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:43:07 by faraz             #+#    #+#             */
/*   Updated: 2022/01/31 12:07:21 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	delimiterlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int	wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	linelen(char const *s, char c)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = 0;
	while (s[i])
	{
		if (flag == 0 && s[i] != c)
		{
			len++;
			flag = 1;
		}
		else if (flag == 1 && s[i] == c)
			flag = 0;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		llen;
	int		clen;
	char	**result;

	if (!s)
		return (0);
	llen = linelen(s, c);
	result = (char **)malloc(sizeof(char *) * (llen + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	clen = 0;
	while (i < llen)
	{
		j += clen + delimiterlen(&s[j + clen], c);
		clen = wordlen(&s[j], c);
		result[i] = (char *)malloc(sizeof(char) * (clen + 1));
		if (result[i])
			ft_strlcpy(result[i++], &s[j], clen + 1);
	}
	result[i] = 0;
	return (result);
}
