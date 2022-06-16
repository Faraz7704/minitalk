/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:47 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/16 18:27:19 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_event_data	g_data;

static void	del(void *content)
{
	free(content);
}

static void	print_buffer(void)
{
	t_list	*curr;

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

static void	char_received(void)
{
	char	*new_char;

	if (g_data.c == 0)
	{
		if (kill(g_data.client_pid, SIGUSR2) == -1)
			exit(0);
		print_buffer();
		g_data.client_pid = 0;
	}
	else if (kill(g_data.client_pid, SIGUSR1) == -1)
		exit(0);
	new_char = ft_strdup((const char *)&g_data.c);
	if (!g_data.buffer)
		g_data.buffer = ft_lstnew(new_char);
	else
		ft_lstadd_back(&g_data.buffer, ft_lstnew(new_char));
	g_data.c = 0;
}

static void	bit_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (!g_data.client_pid)
		g_data.client_pid = info->si_pid;
	else if (info->si_pid != 0 && g_data.client_pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	g_data.index--;
	g_data.c = g_data.c | (sig == SIGUSR1) << g_data.index;
	if (g_data.index == 0)
	{
		g_data.index = 8;
		char_received();
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	bit_action;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	g_data.index = 8;
	bit_action.sa_sigaction = bit_handler;
	bit_action.sa_flags = SA_SIGINFO;
	sigemptyset(&bit_action.sa_mask);
	sigaddset(&bit_action.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &bit_action, NULL) == -1
		|| sigaction(SIGUSR2, &bit_action, NULL) == -1)
	{
		if (g_data.buffer)
			ft_lstclear(&g_data.buffer, del);
		exit(0);
		ft_printf("ERROR: Signal cannot be established\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
