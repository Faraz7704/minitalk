/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/17 16:29:17 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <time.h>

t_client_info	g_info;

static int	send_bit(t_client_info *info)
{
	info->bit_index--;
	if (info->bit_index < 0)
	{
		info->bit_index = 7;
		info->c = *(++info->str);
	}
	if (info->c >> info->bit_index & 1)
	{
		if (kill(info->server_pid, SIGUSR1) == -1)
			return (0);
	}
	else
	{
		if (kill(info->server_pid, SIGUSR2) == -1)
			return (0);
	}
	return (1);
}

static void	received_handler(int sig)
{
	static int	count = 0;

	if (sig == SIGUSR1)
	{
		if (g_info.bit_index - 1 == 0)
			count++;
		if (!send_bit(&g_info))
		{
			ft_printf("\nERROR: Signal cannot be sent ");
			ft_printf("to server with pid: %d\n", g_info.server_pid);
			exit(0);
		}
	}
	else if (sig == SIGUSR2)
	{
		if (!count)
			ft_printf("ERROR: Server is busy, please try again later.\n");
		else
		{
			ft_printf("INFO: Message sent successfully ");
			ft_printf("{char count: %d}\n", count - 1);
		}
		exit(0);
	}
}

int	main(int ac, char **av)
{
	if (ac != 3 || !ft_strlen(av[2]))
	{
		ft_printf("ERROR: Invailed arguments\n");
		exit(0);
		return (1);
	}
	signal(SIGUSR1, received_handler);
	signal(SIGUSR2, received_handler);
	g_info.server_pid = atoi(av[1]);
	g_info.str = av[2];
	g_info.bit_index = 8;
	g_info.c = av[2][0];
	if (!send_bit(&g_info))
	{
		ft_printf("\nERROR: Signal cannot be sent ");
		ft_printf("to server with pid: %d\n", g_info.server_pid);
		exit(0);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
