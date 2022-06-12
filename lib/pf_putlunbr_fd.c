/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putlunbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:29:29 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/16 18:59:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putlsign(int fd, struct s_data data)
{
	int	len;

	len = 0;
	if (data.is_positive_sign)
	{
		write(fd, "+", 1);
		len += 1;
	}
	else if (data.is_space)
	{
		write(fd, " ", 1);
		len += 1;
	}
	return (len);
}

static unsigned int	ft_udigitlen(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
		i++;
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	ft_putunbr_fd(unsigned int nbr, int fd)
{
	char	c;

	if (nbr / 10)
		ft_putunbr_fd(nbr / 10, fd);
	ft_putchar_fd(c = nbr % 10 + '0', fd);
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

int	pf_putlunbr_fd(unsigned int nbr, int fd, struct s_data data)
{
	int	len;
	int	p;

	len = ft_putlsign(fd, data);
	if (nbr == 0 && data.is_precision)
		len = 0;
	else
		len += (int)ft_udigitlen(nbr);
	p = ft_preclen(len, data);
	if (!data.is_left_justify)
		len += pf_width(data.width - len - p, data.is_zero, fd);
	while (p-- > 0)
		len += write(fd, "0", 1);
	if (!data.is_precision || (nbr != 0 && data.is_precision))
		ft_putunbr_fd(nbr, fd);
	if (data.is_left_justify)
		len += pf_width(data.width - len, data.is_zero, fd);
	return (len);
}
