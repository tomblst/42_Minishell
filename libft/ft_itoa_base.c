/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:31:36 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/21 10:19:23 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(unsigned long nbr, int base_len)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= base_len;
		count++;
	}
	return (count);
}

static int	is_valid_base(const char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] > 126)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i >= 2);
}

static char	*ft_allocate(unsigned long nbr, int len, const char *base, int neg)
{
	int		count;
	char	*result;

	count = ft_count_digits(nbr, len) + neg;
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[count] = '\0';
	while (count > neg)
	{
		result[--count] = base[nbr % len];
		nbr /= len;
	}
	if (neg)
		result[0] = '-';
	return (result);
}

char	*ft_itoa_base(long n, const char *base)
{
	int				base_len;
	unsigned long	nbr;
	int				neg;

	if (!is_valid_base(base))
		return (NULL);
	base_len = 0;
	while (base[base_len])
		base_len++;
	neg = (n < 0 && base_len == 10);
	if (n < 0)
		nbr = (unsigned long)(-n);
	else
		nbr = (unsigned long)n;
	return (ft_allocate(nbr, base_len, base, neg));
}
