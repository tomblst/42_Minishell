/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:01:40 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 11:07:24 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_ast *ast, t_ast *ast_init)
{
	int		old_in;
	int		old_out;

	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);
	if (!ast)
		return (ast_init->env->exit_status = 1, 1);
	if (ast->type == AST_HEREDOC)
		handle_redir_heredoc(ast, old_in, old_out);
	else if (ast->type == AST_REDIR_OUT)
		execute_redirection(ast, old_in, old_out, O_WRONLY | O_CREAT | O_TRUNC);
	else if (ast->type == AST_PIPE)
		execute_pipe(ast, old_in, old_out, ast_init);
	else if (ast->type == AST_APPEND)
		execute_redirection(ast, old_in, old_out, O_WRONLY \
			| O_CREAT | O_APPEND);
	else if (ast->type == AST_REDIR_IN)
		execute_redirection(ast, old_in, old_out, O_RDONLY);
	else if (ast->type == AST_COMMAND)
		return (execute_command(ast, &(ast_init->env)));
	restore_dup(old_in, old_out);
	return (1);
}

int	execute_builtin(t_env **env, char **args, t_ast *ast)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(env, args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(env, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(env, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args, *env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, ast, env));
	return (1);
}

void	restore_dup(int old_in, int old_out)
{
	dup2(old_in, STDIN_FILENO);
	dup2(old_out, STDOUT_FILENO);
	close(old_in);
	close(old_out);
}
