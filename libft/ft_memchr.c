/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:14:39 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/11 17:49:00 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		target;
	size_t				i;

	str = (const unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if ((str[i]) == target)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
