/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:38:37 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 11:50:37 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	if (type == TOKEN_DQUOTE || type == TOKEN_SQUOTE)
		token->quote_type = type;
	else
		token->quote_type = 0;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(type, value);
	if (!new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
