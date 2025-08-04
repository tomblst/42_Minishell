/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:16:20 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/15 18:02:54 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s)
		return (d);
	if (d < s)
		ft_memcpy(dest, src, n);
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}
/*copie n caractere de src dans dest en gerant pour les chevauchements */
