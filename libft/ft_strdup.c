/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:16:32 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/12 15:36:14 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*copy;

	size = ft_strlen(str) + 1;
	copy = malloc(size);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, str, size);
	return (copy);
}
//copi une string dans un autre tableau
