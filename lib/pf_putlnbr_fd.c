/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putlnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:32:17 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/16 18:57:42 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_putnbr_fd(int nbr, int fd)
{
	char	c;

	if (nbr < 0)
		nbr *= -1;
	if (nbr / 10)
		pf_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(c = nbr % 10 + '0', fd);
}

static int	ft_putlsign(int nbr, int fd, struct s_data data)
{
	int	len;

	len = 0;
	if (nbr >= 0 && data.is_positive_sign)
	{
		write(fd, "+", 1);
		len += 1;
	}
	else if (nbr >= 0 && data.is_space)
	{
		write(fd, " ", 1);
		len += 1;
	}
	return (len);
}

static int	ft_preclen(int nbr, int len, struct s_data data)
{
	int	preclen;

	if (data.is_precision)
	{
		preclen = data.precision - len + (nbr < 0);
		if (preclen < 0)
			preclen = 0;
	}
	else
		preclen = 0;
	return (preclen);
}

int	pf_putlnbr_fd(int nbr, int fd, struct s_data data)
{
	int	len;
	int	p;

	len = ft_putlsign(nbr, fd, data);
	if (nbr < 0 && data.is_zero)
		ft_putchar_fd('-', fd);
	if (nbr == 0 && data.is_precision)
		len = 0;
	else
		len += ft_digitlen(nbr);
	p = ft_preclen(nbr, len, data);
	if (!data.is_left_justify)
		len += pf_width(data.width - len - p, data.is_zero, fd);
	if (nbr < 0 && !data.is_zero)
		ft_putchar_fd('-', fd);
	while (p-- > 0)
		len += write(fd, "0", 1);
	if (nbr == -2147483648)
		ft_putstr_fd("2147483648", fd);
	else if (!data.is_precision || (nbr != 0 && data.is_precision))
		pf_putnbr_fd(nbr, fd);
	if (data.is_left_justify)
		len += pf_width(data.width - len, data.is_zero, fd);
	return (len);
}
