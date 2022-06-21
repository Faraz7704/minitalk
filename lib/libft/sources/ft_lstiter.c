/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:36:52 by faraz             #+#    #+#             */
/*   Updated: 2022/01/11 00:37:18 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next_lst;

	if (!lst)
		return ;
	next_lst = lst;
	while (next_lst)
	{
		f(next_lst->content);
		next_lst = next_lst->next;
	}
}
