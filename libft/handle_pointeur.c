/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointeur.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:41:16 by tbellest          #+#    #+#             */
/*   Updated: 2024/12/03 13:14:53 by tbellest         ###   ########.fr       */
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

void	ft_put_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	handle_pointeur(va_list parameters)
{
	void				*ptr;
	unsigned long long	address;
	int					count;

	ptr = va_arg(parameters, void *);
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	address = (unsigned long long)ptr;
	count = write(1, "0x", 2);
	ft_put_ptr(address);
	count += ft_count_digits(address, 16);
	return (count);
}
