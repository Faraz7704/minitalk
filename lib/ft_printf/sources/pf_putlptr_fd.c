/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putlptr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:53:45 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/15 23:03:43 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putlptr_fd(unsigned long long ptr, int fd, struct s_data data)
{
	int	len;

	len = 2;
	if (ptr == 0)
		len++;
	else
		len += ft_hexlen(ptr);
	if (!data.is_left_justify)
		len += pf_width(data.width - len, data.is_zero, fd);
	ft_putstr_fd("0x", 1);
	if (ptr == 0)
		write(1, "0", 1);
	else
		ft_puthex(ptr, fd, 0);
	if (data.is_left_justify)
		len += pf_width(data.width - len, data.is_zero, fd);
	return (len);
}
