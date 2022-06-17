/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/17 16:09:30 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server_info	g_info;

static void	del(void *content)
{
	free(content);
}

static void	print_buffer(void)
{
	t_list	*curr;

	curr = g_info.buffer;
	while (curr)
	{
		ft_printf("%c", *(char *)curr->content);
		curr = curr->next;
	}
	ft_printf("\n");
	if (g_info.buffer)
		ft_lstclear(&g_info.buffer, del);
}

static void	char_received(void)
{
	char	*new_char;

	if (g_info.c == 0)
	{
		if (kill(g_info.client_pid, SIGUSR2) == -1)
		{
			if (g_info.buffer)
				ft_lstclear(&g_info.buffer, del);
			exit(0);
		}
		print_buffer();
		g_info.client_pid = 0;
		g_info.c = 0;
	}
	else
	{
		new_char = ft_strdup((const char *)&g_info.c);
		if (!g_info.buffer)
			g_info.buffer = ft_lstnew(new_char);
		else
			ft_lstadd_back(&g_info.buffer, ft_lstnew(new_char));
		if (g_info.c != 0)
		{
			g_info.c = 0;
			if (kill(g_info.client_pid, SIGUSR1) == -1)
			{
				if (g_info.buffer)
					ft_lstclear(&g_info.buffer, del);
				exit(0);
			}
		}
	}
}

static void	bit_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (!g_info.client_pid)
		g_info.client_pid = info->si_pid;
	else if (info->si_pid != 0 && g_info.client_pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	g_info.bit_index--;
	g_info.c = g_info.c | (sig == SIGUSR1) << g_info.bit_index;
	if (g_info.bit_index == 0)
	{
		g_info.bit_index = 8;
		char_received();
	}
	else
	{
		if (kill(g_info.client_pid, SIGUSR1) == -1)
		{
			if (g_info.buffer)
				ft_lstclear(&g_info.buffer, del);
			exit(0);
		}
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	bit_action;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	g_info.bit_index = 8;
	bit_action.sa_sigaction = bit_handler;
	bit_action.sa_flags = SA_SIGINFO;
	sigemptyset(&bit_action.sa_mask);
	sigaddset(&bit_action.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &bit_action, NULL) == -1
		|| sigaction(SIGUSR2, &bit_action, NULL) == -1)
	{
		if (g_info.buffer)
			ft_lstclear(&g_info.buffer, del);
		exit(0);
		ft_printf("ERROR: Signal cannot be established\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
