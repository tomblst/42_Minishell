/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:45:54 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/16 16:15:54 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*conteur;

	conteur = lst;
	if (!lst)
		return (NULL);
	while (conteur->next)
		conteur = conteur->next;
	return (conteur);
}
//Renvoie le dernier élément de la liste.
