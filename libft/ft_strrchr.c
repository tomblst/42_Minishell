/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:04:39 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/12 12:18:51 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == (char)c)
			return ((char *)str + len);
		len--;
	}
	if (str[len] == (char)c)
		return ((char *)str + len);
	return (NULL);
}
//cherche une occurence en partant de la fin
