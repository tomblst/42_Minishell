/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:50:41 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 13:52:56 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*handle_heredoc(t_token **current, t_ast **ast, int *a_count)
{
	t_ast	*redir;
	char	*filename;
	t_cmd	*new_command;

	filename = execute_redir_heredoc((*current)->next->value);
	*current = (*current)->next;
	if (!filename)
		return (free_ast(*ast), NULL);
	redir = new_ast_node(AST_HEREDOC, NULL);
	if (!redir)
		return (free(filename), free_ast(*ast), NULL);
	redir->filename = filename;
	if (*ast)
		redir->left = *ast;
	if ((*current)->next && (*current)->next->type == TOKEN_WORD)
	{
		*current = (*current)->next;
		new_command = new_cmd();
		if (!new_command)
			return (free_ast(redir), free_ast(*ast), NULL);
		parse_token_word(*current, &new_command, a_count);
		redir->right = new_ast_node(AST_COMMAND, new_command);
	}
	return (redir);
}

static t_ast	*handle_mult_redir(t_ast **ast, t_ast *redir, char *filename)
{
	int	fd;

	if ((*ast)->type == AST_REDIR_OUT)
		fd = open((*ast)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open((*ast)->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		free(filename);
		free_ast(redir);
		free_ast(*ast);
		return (NULL);
	}
	close(fd);
	free((*ast)->filename);
	(*ast)->filename = filename;
	(*ast)->type = redir->type;
	free(redir);
	return (*ast);
}

static t_ast	*handle_redir(t_token **current, t_ast **ast)
{
	t_ast	*redir;
	char	*filename;

	redir = new_ast_node(token_to_ast_type((*current)->type), NULL);
	if (!redir)
		return (free_ast(*ast), NULL);
	redir->left = *ast;
	*current = (*current)->next;
	filename = ft_strdup((*current)->value);
	if (!filename)
		return (free_ast(redir), free_ast(*ast), NULL);
	redir->filename = filename;
	if (!redir->filename)
		return (free_ast(redir), free_ast(*ast), NULL);
	if (*ast && ((*ast)->type == AST_REDIR_OUT || (*ast)->type == AST_APPEND))
	{
		*ast = handle_mult_redir(ast, redir, filename);
		return (*ast);
	}
	return (redir);
}

t_ast	*parse_t_redir(t_token **cur, t_ast **ast, t_cmd **cmd, int *a_count)
{
	t_ast	*redir;
	t_cmd	*new_command;

	if (*cmd && *a_count > 0 && !(*ast))
	{
		*ast = new_ast_node(AST_COMMAND, *cmd);
		*cmd = NULL;
		*a_count = 0;
	}
	if (!(*cur)->next || (*cur)->next->type != TOKEN_WORD)
		return (free_ast(*ast), NULL);
	if ((*cur)->type == TOKEN_HEREDOC)
		return (redir = handle_heredoc(cur, ast, a_count));
	redir = handle_redir(cur, ast);
	if ((*cur)->next && (*cur)->next->type == TOKEN_WORD)
	{
		*cur = (*cur)->next;
		new_command = new_cmd();
		if (!new_command)
			return (free_ast(redir), free_ast(*ast), NULL);
		parse_token_word(*cur, &new_command, a_count);
		redir->left = new_ast_node(AST_COMMAND, new_command);
	}
	return (redir);
}
