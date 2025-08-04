/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:22:14 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/21 10:23:57 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char_string(va_list parameters, char ch)
{
	int		count;
	char	c;
	char	*s;

	count = 0;
	if (ch == 'c')
	{
		c = (char)va_arg(parameters, int);
		ft_putchar_fd(c, 1);
		count++;
	}
	if (ch == 's')
	{
		s = va_arg(parameters, char *);
		if (!s)
			s = "(null)";
		ft_putstr_fd(s, 1);
		count += ft_strlen(s);
	}
	return (count);
}
