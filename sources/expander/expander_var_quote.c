/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:22:11 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/28 10:39:06 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_single_quote(const char *input, t_result *res, int *i)
{
	res->result[res->j++] = input[(*i)++];
	res->result[res->j++] = input[(*i)++];
	while (input[*i] && input[*i] != '\'' && res->j < 1023)
		res->result[res->j++] = input[(*i)++];
	if (input[*i] == '\'')
		res->result[res->j++] = input[(*i)++];
}

static void	process_char(char *input, t_env *env, t_result *res, int *state)
{
	if (input[res->i] == '$' && *state != QUOTE_SINGLE)
		process_dollar(input, env, res, &res->i);
	else
	{
		update_quote_state(input[(res)->i], state);
		res->result[res->j++] = input[(res->i)++];
	}
}

char	*expand_variable_with_quotes(const char *input, t_env *env)
{
	char		*result;
	t_result	res;
	int			state;

	result = ft_calloc(MAX_EXPANSION_SIZE, 1);
	if (!result)
		return (NULL);
	res.i = 0;
	res.j = 0;
	res.result = result;
	state = QUOTE_NONE;
	while (input[res.i] && res.j < 1023)
	{
		if (input[res.i] == '$' && input[res.i + 1] == '\'')
		{
			process_single_quote(input, &res, &res.i);
			continue ;
		}
		process_char((char *)input, env, &res, &state);
	}
	res.result[res.j] = '\0';
	return (res.result);
}
