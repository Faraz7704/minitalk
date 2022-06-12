/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/12 18:39:02 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	received_handler(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		received++;
	else if (sig == SIGUSR2)
	{
		ft_printf("INFO: Message sent successfully {sig count: %d}\n", received);
		exit(0);
	}
}

static int	send_char_server(unsigned char c, int server_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (0);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				return (0);
		}
		usleep(100);
	}
	return (1);
}

static int	send_string_server(const char *str, int server_pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!send_char_server(str[i], server_pid))
			return (0);
		i++;
	}
	if (!send_char_server('\0', server_pid))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	pid_t				server_pid;

	if (ac != 3 || !ft_strlen(av[2]))
	{
		ft_printf("ERROR: Invailed arguments\n");
		exit(0);
		return (1);
	}
	signal(SIGUSR1, received_handler);
	signal(SIGUSR2, received_handler);
	server_pid = atoi(av[1]);
	if (!send_string_server(av[2], server_pid))
	{
		ft_printf("ERROR: Signal cannot be sent ");
		ft_printf("to server with pid: %d\n", server_pid);
		exit(0);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
