/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuellar <lcuellar@student42.madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:23:54 by lcuellar          #+#    #+#             */
/*   Updated: 2023/09/16 23:42:27 by lcuellar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;
	t_list	*aux2;

	aux = *lst;
	while (aux)
	{
		aux2 = aux -> next;
		ft_lstdelone(aux, del);
		aux = aux2;
	}
	*lst = NULL;
}
