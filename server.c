/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/12 18:40:26 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_event_data	g_data;

static void	bit_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (!g_data.client_pid)
		g_data.client_pid = info->si_pid;
	g_data.c = g_data.c | (sig == SIGUSR1) << --g_data.index;
}

static void	del(void *content)
{
	free(content);
}

static void	print_buffer(void)
{
	t_list	*curr;

	g_data.client_pid = 0;
	curr = g_data.buffer;
	while (curr)
	{
		ft_printf("%c", *(char *)curr->content);
		curr = curr->next;
	}
	ft_printf("\n");
	if (g_data.buffer)
		ft_lstclear(&g_data.buffer, del);
}

static int	main_loop(void)
{
	char	*new_char;

	while (1)
	{
		pause();
		if (g_data.index == 0)
		{
			if (g_data.c == 0)
			{
				if (kill(g_data.client_pid, SIGUSR2) == -1)
					return (0);
				print_buffer();
			}
			else if (kill(g_data.client_pid, SIGUSR1) == -1)
				return (0);
			new_char = ft_strdup((const char *)&g_data.c);
			if (!g_data.buffer)
				g_data.buffer = ft_lstnew(new_char);
			else
				ft_lstadd_back(&g_data.buffer, ft_lstnew(new_char));
			g_data.c = 0;
			g_data.index = 8;
		}
	}
	return (1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	bit_action;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	bit_action.sa_sigaction = bit_handler;
	bit_action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &bit_action, NULL) == -1
		|| sigaction(SIGUSR2, &bit_action, NULL) == -1)
	{
		if (g_data.buffer)
			ft_lstclear(&g_data.buffer, del);
		exit(0);
		ft_printf("ERROR: Signal cannot be established\n");
		return (1);
	}
	g_data.index = 8;
	if (!main_loop())
	{
		exit(0);
		ft_printf("ERROR: Cannot send signal to client\n");
		return (1);
	}
	return (0);
}
