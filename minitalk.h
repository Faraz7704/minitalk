/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:39:23 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/16 17:47:51 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "lib/libft/libft.h"
# include "lib/ft_printf.h"

typedef struct s_event_data
{
	int				client_pid;
	t_list			*buffer;
	int				index;
	unsigned char	c;
}	t_event_data;

#endif