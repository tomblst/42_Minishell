/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:08:45 by tbellest          #+#    #+#             */
/*   Updated: 2024/11/20 19:00:44 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int	handle_char_string(va_list parameters, char ch);
int	ft_printf(const char *string, ...);
int	handle_integer(va_list parameters, char ch);
int	handle_hex(va_list parameters, char ch);
int	handle_pointeur(va_list parameters);

#endif
