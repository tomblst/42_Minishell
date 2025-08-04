/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:26:05 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 13:52:49 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_token(t_token *tokens)
{
	t_ast	*ast;
	t_cmd	*cmd;
	t_token	*current;
	int		args_count;

	ast = NULL;
	cmd = NULL;
	current = tokens;
	args_count = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			return (parse_t_pipe(&current, &ast, &cmd, &args_count));
		else if (current->type == TOKEN_WORD)
			parse_token_word(current, &cmd, &args_count);
		else if (is_redir(current->value))
			ast = parse_t_redir(&current, &ast, &cmd, &args_count);
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	if (cmd && !ast)
		ast = new_ast_node(AST_COMMAND, cmd);
	return (ast);
}

void	parse_token_word(t_token *current, t_cmd **cmd, int *args_count)
{
	size_t	old_size;
	size_t	new_size;

	if (!(*cmd))
	{
		*cmd = new_cmd();
		if (!*cmd)
			return ;
	}
	if ((*cmd)->args)
		old_size = sizeof(char *) * (*args_count + 1);
	else
		old_size = 0;
	new_size = sizeof(char *) * (*args_count + 2);
	(*cmd)->args = ft_realloc((*cmd)->args, old_size, new_size);
	if (!(*cmd)->args)
	{
		free_cmd(*cmd);
		return ;
	}
	(*cmd)->args[*args_count] = ft_strdup(current->value);
	if (!(*cmd)->args[*args_count])
		return (free_cmd(*cmd));
	(*cmd)->args[*args_count + 1] = NULL;
	(*args_count)++;
}

t_ast	*parse_t_pipe(t_token **cur, t_ast **ast, t_cmd **cmd, int *a_count)
{
	t_ast	*new_pipe;

	if (*cmd)
	{
		*ast = new_ast_node(AST_COMMAND, *cmd);
		*cmd = NULL;
		*a_count = 0;
	}
	if (!*ast)
		return (NULL);
	new_pipe = new_ast_node(AST_PIPE, NULL);
	if (!new_pipe)
		return (free_ast(*ast), NULL);
	new_pipe->left = *ast;
	*cur = (*cur)->next;
	if (!(*cur))
		return (free_ast(new_pipe), free_ast(*ast), NULL);
	new_pipe->right = parse_token((*cur));
	if (!new_pipe->right)
		return (free_ast(new_pipe), free_ast(*ast), NULL);
	return (new_pipe);
}
