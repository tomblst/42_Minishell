/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:34:21 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/13 18:29:03 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*s2;

	start = 0;
	end = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strrchr(set, s1[end - 1]))
		end--;
	len = end - start;
	s2 = malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &s1[start], len + 1);
	return (s2);
}
/* Alloue (avec malloc(3)) et retourne une copie de
la chaîne ’s1’, sans les caractères spécifiés
dans ’set’ au début et à la fin de la chaîne de
caractères */
