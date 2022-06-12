/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:00:05 by fkhan             #+#    #+#             */
/*   Updated: 2022/02/16 19:06:38 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_resetdata(struct s_data *data)
{
	data->width = 0;
	data->is_precision = 0;
	data->is_left_justify = 0;
	data->is_zero = 0;
	data->is_hash = 0;
	data->is_positive_sign = 0;
	data->is_space = 0;
	data->precision = 0;
}

static int	ft_isflag(char c)
{
	if (c == '-' || c == '0' || c == '#' || c == ' ' || c == '+')
		return (1);
	return (0);
}

static void	pf_setflagbool(const char *flag, struct s_data *data)
{
	while (*flag && ft_isflag(*flag))
	{
		if (*flag == '-')
			data->is_left_justify = 1;
		else if (*flag == '0')
			data->is_zero = 1;
		else if (*flag == '#')
			data->is_hash = 1;
		else if (*flag == '+')
			data->is_positive_sign = 1;
		else if (*flag == ' ')
			data->is_space = 1;
		flag++;
	}
}

static void	pf_setflagvalue(const char **flag, struct s_data *data)
{
	while (**flag && ft_isflag(**flag))
		(*flag)++;
	while (**flag && (ft_isdigit(**flag) || **flag == '.'))
	{
		if (**flag == '.')
		{
			data->is_precision = 1;
			(*flag)++;
			if (ft_isdigit(**flag))
			{
				data->precision = ft_atoi(*flag);
				*flag += ft_digitlen(data->precision);
			}
		}
		else if (!data->width)
		{
			data->width = ft_atoi(*flag);
			*flag += ft_digitlen(data->width);
		}
	}
}

struct s_data	ft_parse_flags(const char **flag)
{
	struct s_data	data;

	pf_resetdata(&data);
	pf_setflagbool(*flag, &data);
	pf_setflagvalue(flag, &data);
	if (data.is_zero && data.is_precision)
		data.is_zero = 0;
	return (data);
}
