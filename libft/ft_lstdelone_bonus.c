/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:35:25 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/17 15:49:33 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free (lst);
}
/* Libère la mémoire de l’élément passé en argument en
utilisant la fonction ’del’ puis avec free(3). La
mémoire de ’next’ ne doit pas être free. */
