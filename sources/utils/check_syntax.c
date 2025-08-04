/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:51:14 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/14 14:25:38 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_redir_error_token(t_token *token)
{
	if (!token->next)
		return (ft_strdup("newline"));
	if (token->next->type != TOKEN_WORD)
		return (ft_strdup(token->next->value));
	return (ft_strdup("newline"));
}

static int	check_pipe(t_token *token, t_token *prev_token)
{
	if (!prev_token || prev_token->type == TOKEN_PIPE)
	{
		print_syntax_error(token->value);
		return (0);
	}
	if (!token->next || token->next->type == TOKEN_PIPE)
	{
		if (!token->next)
			print_syntax_error("newline");
		else
			print_syntax_error(token->next->value);
		return (0);
	}
	return (1);
}

static int	check_redirection(t_token *token)
{
	char	*error_token;

	if (!token->next || token->next->type != TOKEN_WORD)
	{
		error_token = get_redir_error_token(token);
		if (!error_token)
			return (0);
		print_syntax_error(error_token);
		free(error_token);
		return (0);
	}
	return (1);
}

static int	is_valid_token(t_token *token, t_token *prev_token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || \
		token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
	{
		return (check_redirection(token));
	}
	else if (token->type == TOKEN_PIPE)
		return (check_pipe(token, prev_token));
	return (1);
}

int	check_syntax(t_token *token)
{
	t_token	*current;
	t_token	*prev;

	current = token;
	prev = NULL;
	while (current)
	{
		if (is_valid_token(current, prev) != 1)
			return (0);
		prev = current;
		current = current->next;
	}
	return (1);
}
