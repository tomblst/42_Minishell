/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:38:20 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 15:53:37 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_operator_type(char *line, int *i)
{
	if (line[*i] == '|')
		return (TOKEN_PIPE);
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIR_IN);
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

static void	handle_operator(char *line, int *i, t_token **tokens)
{
	t_token_type	type;
	char			buffer[3];
	int				j;

	j = 0;
	type = get_operator_type(line, i);
	buffer[j++] = line[(*i)++];
	if ((type == TOKEN_HEREDOC || type == TOKEN_APPEND) \
	&& line[*i] == buffer[0])
		buffer[j++] = line[(*i)++];
	buffer[j] = '\0';
	add_token(tokens, buffer, type);
}

static void	process_quotes(char *line, int *i, int *state)
{
	if (line[*i] == '\'' && *state != QUOTE_DOUBLE)
	{
		if (*state == QUOTE_SINGLE)
			*state = QUOTE_NONE;
		else
			*state = QUOTE_SINGLE;
	}
	else if (line[*i] == '"' && *state != QUOTE_SINGLE)
	{
		if (*state == QUOTE_DOUBLE)
			*state = QUOTE_NONE;
		else
			*state = QUOTE_DOUBLE;
	}
}

static void	add_word_token(char *line, int *i, t_token **tokens)
{
	char	buffer[1024];
	int		j;
	int		state;

	j = 0;
	state = QUOTE_NONE;
	while (line[*i] && (!ft_isspace(line[*i]) || state != \
	QUOTE_NONE))
	{
		process_quotes(line, i, &state);
		if (is_operator(line[*i]) && state == QUOTE_NONE)
			break ;
		buffer[j++] = line[(*i)++];
	}
	buffer[j] = '\0';
	add_token(tokens, buffer, TOKEN_WORD);
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			handle_operator(line, &i, &tokens);
		else
			add_word_token(line, &i, &tokens);
	}
	return (tokens);
}
