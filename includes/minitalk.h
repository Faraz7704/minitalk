/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:23 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/20 18:52:23 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_server_info
{
	int				client_pid;
	t_list			*buffer;
	int				bit_index;
	unsigned char	c;
}	t_server_info;

typedef struct s_client_info
{
	int				server_pid;
	char			*str;
	int				len;
	int				bit_index;
	unsigned char	c;
}	t_client_info;

#endif