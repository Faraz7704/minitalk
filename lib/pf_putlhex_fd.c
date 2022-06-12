/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putlhex_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:29:29 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/16 19:06:46 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putlsign(int nbr, int fd, int isupper, struct s_data data)
{
	int	len;

	len = 0;
	if (data.is_hash && nbr != 0)
	{
		if (isupper)
			write(fd, "0X", 2);
		else
			write(fd, "0x", 2);
		len = 2;
	}
	return (len);
}

static int	ft_preclen(int len, struct s_data data)
{
	int	preclen;

	if (data.is_precision)
	{
		preclen = data.precision - len;
		if (preclen < 0)
			preclen = 0;
	}
	else
		preclen = 0;
	return (preclen);
}

int	pf_putlhex_fd(unsigned int nbr, int fd, int isupper, struct s_data data)
{
	int	len;
	int	p;

	len = ft_putlsign(nbr, fd, isupper, data);
	if (nbr == 0 && data.is_precision)
		len = 0;
	else if (nbr == 0)
		len++;
	else
		len += ft_hexlen(nbr);
	p = ft_preclen(len, data);
	if (!data.is_left_justify)
		len += pf_width(data.width - len - p, data.is_zero, fd);
	while (p-- > 0)
		len += write(fd, "0", 1);
	if (nbr == 0 && !data.is_precision)
		write(fd, "0", 1);
	else if (!data.is_precision || (nbr != 0 && data.is_precision))
		ft_puthex(nbr, fd, isupper);
	if (data.is_left_justify)
		len += pf_width(data.width - len, data.is_zero, fd);
	return (len);
}
