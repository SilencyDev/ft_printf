/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:58:37 by kmacquet          #+#    #+#             */
/*   Updated: 2021/01/26 17:50:50 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*isworking;

	newlist = NULL;
	if (lst)
	{
		newlist = ft_lstnew(f(lst->content));
		if (newlist)
		{
			lst = lst->next;
			while (lst)
			{
				if (!(isworking = ft_lstnew(f(lst->content))))
					ft_lstclear(&newlist, del);
				ft_lstadd_back(&newlist, isworking);
				lst = lst->next;
			}
		}
	}
	return (newlist);
}
