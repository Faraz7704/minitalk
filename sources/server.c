/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/21 14:21:59 by fkhan            ###   ########.fr       */
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
		ft_putchar_fd(*(char *)curr->content, 1);
		curr = curr->next;
	}
	ft_putchar_fd('\n', 1);
	if (g_info.buffer)
		ft_lstclear(&g_info.buffer, del);
	g_info.c = 0;
	if (kill(g_info.client_pid, SIGUSR2) == -1)
		exit(0);
	g_info.client_pid = 0;
}

static void	char_received(void)
{
	char	*new_char;

	g_info.bit_index = 8;
	if (g_info.c == 0)
		print_buffer();
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
	if (info->si_pid != 0 && g_info.client_pid != info->si_pid)
	{
		if (g_info.client_pid != 0)
			kill(g_info.client_pid, SIGUSR2);
		if (g_info.buffer)
			ft_lstclear(&g_info.buffer, del);
		g_info.bit_index = 8;
		g_info.c = 0;
	}
	if (info->si_pid != 0)
		g_info.client_pid = info->si_pid;
	g_info.bit_index--;
	g_info.c = g_info.c | (sig == SIGUSR1) << g_info.bit_index;
	if (g_info.bit_index == 0)
		char_received();
	else if (kill(g_info.client_pid, SIGUSR1) == -1)
	{
		if (g_info.buffer)
			ft_lstclear(&g_info.buffer, del);
		ft_printf("ERROR: Confirmation signal cannot be sent to client\n");
		exit(0);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	bit_action;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	bit_action = (struct sigaction){0};
	bit_action.sa_sigaction = bit_handler;
	bit_action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &bit_action, NULL) == -1
		|| sigaction(SIGUSR2, &bit_action, NULL) == -1)
	{
		if (g_info.buffer)
			ft_lstclear(&g_info.buffer, del);
		ft_printf("ERROR: Signal cannot be established\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
