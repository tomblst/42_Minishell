/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:48:36 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/28 10:39:14 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(const char *input)
{
	char	*result;
	int		i;
	int		j;
	int		state;

	result = ft_calloc(ft_strlen(input) + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	state = QUOTE_NONE;
	while (input[i])
	{
		if (is_opening_or_closing_quote(input[i], state))
		{
			process_quote_state(input[i], &state);
			i++;
			continue ;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

int	is_opening_or_closing_quote(char c, int state)
{
	if (c == '\'' && state != QUOTE_DOUBLE)
		return (1);
	if (c == '\"' && state != QUOTE_SINGLE)
		return (1);
	return (0);
}

void	process_quote_state(char c, int *state)
{
	if (c == '\'' && *state != QUOTE_DOUBLE)
	{
		if (*state == QUOTE_SINGLE)
			*state = QUOTE_NONE;
		else
			*state = QUOTE_SINGLE;
	}
	else if (c == '\"' && *state != QUOTE_SINGLE)
	{
		if (*state == QUOTE_DOUBLE)
			*state = QUOTE_NONE;
		else
			*state = QUOTE_DOUBLE;
	}
}

void	update_quote_state(char c, int *state)
{
	if (c == '\'' && *state != QUOTE_DOUBLE)
	{
		if (*state == QUOTE_SINGLE)
			*state = QUOTE_NONE;
		else
			*state = QUOTE_SINGLE;
	}
	else if (c == '\"' && *state != QUOTE_SINGLE)
	{
		if (*state == QUOTE_DOUBLE)
			*state = QUOTE_NONE;
		else
			*state = QUOTE_DOUBLE;
	}
}

int	should_copy_char(char c, int *state)
{
	int	old_state;

	old_state = *state;
	update_quote_state(c, state);
	if ((c == '\'' && (old_state != QUOTE_DOUBLE)) || (c == '\"'
			&& (old_state != QUOTE_SINGLE)))
		return (0);
	return (1);
}
