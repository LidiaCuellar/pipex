/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:45:51 by lcuellar          #+#    #+#             */
/*   Updated: 2023/09/17 00:11:55 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst -> content));
	if (!new)
		return (NULL);
	aux = new;
	lst = lst -> next;
	while (lst)
	{
		aux -> next = ft_lstnew(f(lst -> content));
		if (!aux -> next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		aux = aux -> next;
		lst = lst -> next;
	}
	return (new);
}
