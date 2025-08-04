/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:05:12 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/21 13:35:08 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle(int i, const char *string, va_list parameters)
{
	int	count;

	count = 0;
	if (string[i] == 'c' || string[i] == 's')
		count += handle_char_string(parameters, string[i]);
	if (string[i] == 'i' || string[i] == 'd' || string[i] == 'u')
		count += handle_integer(parameters, string[i]);
	if (string[i] == 'x' || string[i] == 'X')
		count += handle_hex(parameters, string[i]);
	if (string[i] == 'p')
		count += handle_pointeur(parameters);
	if (string[i] == '%')
	{
		ft_putchar_fd('%', 1);
		count++;
	}
	return (count);
}

int	ft_printf(const char *string, ...)
{
	va_list	parameters;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!string)
		return (-1);
	va_start(parameters, string);
	while (string[i])
	{
		if (string[i] != '%')
		{
			ft_putchar_fd(string[i], 1);
			count++;
		}
		if (string[i] == '%')
		{
			i++;
			count += ft_handle(i, string, parameters);
		}
		i++;
	}
	va_end(parameters);
	return (count);
}
