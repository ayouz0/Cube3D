/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:36:47 by aaitabde          #+#    #+#             */
/*   Updated: 2024/11/13 11:03:54 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <libc.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*cnt;

	new_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		cnt = f(lst->content);
		new_node = ft_lstnew(cnt);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			del(cnt);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
