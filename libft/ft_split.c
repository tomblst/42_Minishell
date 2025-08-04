/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:22:37 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/15 10:57:12 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*alloc_word(char const *s, int start, int i)
{
	char	*word;

	word = malloc((i - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &s[start], i - start + 1);
	return (word);
}

static void	free_all(char **array, int split)
{
	while (split > 0)
		free(array[--split]);
	free(array);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i +1] == c || s[i +1] == '\0') && (s[i] != c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**array;
	int		split;
	int		start;

	array = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = ((split = 0));
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > start)
			array[split] = alloc_word(s, start, i);
		if (i > start && !array[split++])
			free_all(array, split);
	}
	return (array[split] = NULL, array);
}
/* Alloue (avec malloc(3)) et retourne un tableau
de chaînes de caractères obtenu en séparant ’s’ à
l’aide du caractère ’c’, utilisé comme délimiteur.
Le tableau doit être terminé par NULL. */
