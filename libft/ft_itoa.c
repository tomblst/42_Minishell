/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:12:27 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/14 12:25:36 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

static int	ft_count(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		count++;
	}
	if (nbr == 0)
		count++;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		count;
	char	*nombre;
	int		i;

	nbr = n;
	count = ft_count(nbr);
	if (nbr < 0)
		nbr = -nbr;
	i = count -1;
	nombre = malloc((count + 1) * sizeof(char));
	if (!nombre)
		return (NULL);
	nombre[count] = '\0';
	while (i >= 0)
	{
		nombre[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	if (n < 0)
		nombre[0] = '-';
	return (nombre);
}
