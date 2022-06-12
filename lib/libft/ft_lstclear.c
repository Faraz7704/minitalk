/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:17:58 by faraz             #+#    #+#             */
/*   Updated: 2022/01/11 00:18:23 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_lst;

	if (!lst[0])
		return ;
	while (lst[0])
	{
		next_lst = lst[0]->next;
		ft_lstdelone(lst[0], del);
		lst[0] = next_lst;
	}
	lst[0] = NULL;
}
