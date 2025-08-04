/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:49:29 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/12 15:03:21 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sousstr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*sousstr == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (sousstr[j] && (str[i + j] == sousstr[j]) && (i + j) < len)
			j++;
		if (sousstr[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
//cherche une string dans une autre string
