/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:57:10 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/16 15:24:57 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*actuel;

	size = 0;
	if (lst == NULL)
		return (0);
	actuel = lst;
	while (actuel != NULL)
	{
		actuel = actuel->next;
		size++;
	}
	return (size);
}
//Compte le nombre d’éléments de la liste.
