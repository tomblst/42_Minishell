/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:03:56 by tbellest          #+#    #+#             */
/*   Updated: 2024/12/02 12:51:03 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_digits(unsigned long long nbr, int base_len)
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

static void	put_hex(unsigned int nombre, char ch)
{
	if (nombre >= 16)
	{
		put_hex(nombre / 16, ch);
		put_hex(nombre % 16, ch);
	}
	else
	{
		if (nombre <= 9)
			ft_putchar_fd((nombre + '0'), 1);
		else
		{
			if (ch == 'x')
				ft_putchar_fd((nombre - 10 + 'a'), 1);
			if (ch == 'X')
				ft_putchar_fd((nombre - 10 + 'A'), 1);
		}
	}
}

int	handle_hex(va_list parameters, char ch)
{
	unsigned int		nombre;

	nombre = va_arg(parameters, unsigned int);
	if (nombre == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	put_hex(nombre, ch);
	return (ft_count_digits(nombre, 16));
}
