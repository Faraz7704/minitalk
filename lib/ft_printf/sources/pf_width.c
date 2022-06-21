/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:29:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/15 23:03:50 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_width(int n, int is_zero, int fd)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (is_zero)
			write(fd, "0", 1);
		else
			write(fd, " ", 1);
		i++;
	}
	return (i);
}
