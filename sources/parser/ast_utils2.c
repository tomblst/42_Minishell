/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:49:34 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 13:49:54 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->is_builtin = 0;
	cmd->next = NULL;
	return (cmd);
}

t_a_ty	token_to_ast_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (AST_REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (AST_REDIR_OUT);
	if (token_type == TOKEN_APPEND)
		return (AST_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (AST_HEREDOC);
	return (AST_ERROR);
}
