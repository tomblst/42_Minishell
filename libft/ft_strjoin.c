/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:27:15 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/12 18:24:07 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*array;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	array = malloc((len1 + len2 + 1) * sizeof(char));
	if (!array)
		return (NULL);
	ft_memcpy(array, s1, len1);
	ft_memcpy(array + len1, s2, len2);
	array[len1 + len2] = '\0';
	return (array);
}
/* Alloue (avec malloc(3)) et retourne une nouvelle
chaîne, résultat de la concaténation de s1 et s2. */
