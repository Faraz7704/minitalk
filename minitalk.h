/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:23 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/17 16:08:03 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "lib/libft/libft.h"
# include "lib/ft_printf.h"

typedef struct s_server_info
{
	int				client_pid;
	t_list			*buffer;
	int				bit_index;
	unsigned char	c;
	unsigned int	last_updated;
}	t_server_info;

typedef struct s_client_info
{
	int				server_pid;
	char			*str;
	int				bit_index;
	unsigned char	c;
}	t_client_info;

#endif