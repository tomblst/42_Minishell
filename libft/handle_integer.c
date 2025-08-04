/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:29:14 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/21 13:30:50 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unsigned_int(va_list parameters, char *str)
{
	unsigned int	uns_nombre;
	int				count;

	count = 0;
	uns_nombre = va_arg(parameters, unsigned int);
	str = ft_utoa(uns_nombre);
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	count += ft_strlen(str);
	free(str);
	return (count);
}

int	handle_integer(va_list parameters, char ch)
{
	int				count;
	int				nombre;
	char			*str;

	count = 0;
	str = NULL;
	if (ch == 'd' || ch == 'i')
	{
		nombre = va_arg(parameters, int);
		str = ft_itoa(nombre);
		if (!str)
			return (-1);
		ft_putstr_fd(str, 1);
		count += ft_strlen(str);
	}
	else if (ch == 'u')
		count += unsigned_int(parameters, str);
	free(str);
	return (count);
}
