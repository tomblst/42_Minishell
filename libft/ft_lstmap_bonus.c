/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:31:10 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/18 11:38:49 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*lst2;

	if (!lst || !f || !del)
		return (NULL);
	lst2 = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&lst2, del);
			return (NULL);
		}
		ft_lstadd_back(&lst2, new_node);
		lst = lst->next;
	}
	return (lst2);
}
/* Itère sur la liste ’lst’ et applique la fonction
’f ’au contenu de chaque élément. Crée une nouvelle
liste résultant des applications successives de
’f’. La fonction ’del’ est là pour détruire le
contenu d’un élément si nécessaire. */
