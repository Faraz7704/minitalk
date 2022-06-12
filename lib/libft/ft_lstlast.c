/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faraz <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:54:42 by faraz             #+#    #+#             */
/*   Updated: 2022/01/10 23:55:06 by faraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*next_lst;

	if (!lst)
		return (0);
	next_lst = lst;
	while (next_lst->next)
		next_lst = next_lst->next;
	return (next_lst);
}
