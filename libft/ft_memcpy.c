/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:18:22 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/16 19:42:41 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*desttt;
	unsigned char	*srccc;
	size_t			i;

	srccc = (unsigned char *)src;
	desttt = (unsigned char *)dest;
	if (!srccc && !desttt)
		return (NULL);
	i = 0;
	while (i < n)
	{
		desttt[i] = srccc[i];
		i++;
	}
	return (dest);
}
//copie n caractere de src dans dst
