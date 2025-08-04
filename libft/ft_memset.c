/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:53:12 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/08 19:28:38 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointeur, int valeur, size_t size)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	value;

	str = (unsigned char *)pointeur;
	value = (unsigned char)valeur;
	i = 0;
	while (i < size)
	{
		str[i] = value;
		i++;
	}
	return (pointeur);
}
