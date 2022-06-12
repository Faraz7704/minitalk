/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:30:35 by faraz             #+#    #+#             */
/*   Updated: 2022/01/10 23:54:20 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*next_lst;

	if (!lst)
		return (0);
	next_lst = lst;
	i = 0;
	while (next_lst)
	{
		i++;
		next_lst = next_lst->next;
	}
	return (i);
}
