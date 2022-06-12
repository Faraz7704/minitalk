/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:03:20 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/15 23:03:29 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(uintptr_t num, int fd, int isupper)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, fd, isupper);
		ft_puthex(num % 16, fd, isupper);
	}
	else
	{
		if (num < 10)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (isupper)
				ft_putchar_fd((num - 10 + 'A'), fd);
			else
				ft_putchar_fd((num - 10 + 'a'), fd);
		}
	}
}
