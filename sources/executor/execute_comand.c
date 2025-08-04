/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:01:51 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 11:10:21 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_command_errors(t_cmd *cmd, t_ast *ast, t_env **env)
{
	struct stat	sb;

	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		(*env)->exit_status = 127;
		exit(127);
	}
	if (stat(cmd->path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			printf("minishell: %s: is a directory\n", cmd->args[0]);
			free_ast_fork(ast);
			rl_clear_history();
			(*env)->exit_status = 126;
			exit(126);
		}
	}
}

static void	handle_execve(t_cmd *cmd, t_ast *ast, t_env **env)
{
	reset_signals_for_child();
	check_command_errors(cmd, ast, env);
	if (execve(cmd->path, cmd->args, ast->env_array) == -1)
	{
		perror("execve");
		free_cmd(cmd);
		(*env)->exit_status = 127;
		exit(127);
	}
	free_cmd(cmd);
}

static int	execute_fork(t_cmd *cmd, t_ast *ast, t_env **env, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), 1);
	if (*pid == 0)
		handle_execve(cmd, ast, env);
	return (0);
}

static int	execute_waitpid(pid_t pid, t_env **env)
{
	int	status;

	waitpid(pid, &status, 0);
	g_signal_status = 0;
	handle_child_signal(status, env);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (1);
}

int	execute_command(t_ast *ast, t_env **env)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = ast->cmd;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	expand_command(cmd, *env);
	resolve_cmd(cmd, env);
	if (cmd->is_builtin)
		return ((*env)->exit_status = execute_builtin(env, cmd->args, ast));
	if (!cmd->path)
		return ((*env)->exit_status = 127);
	g_signal_status = 1;
	if (execute_fork(cmd, ast, env, &pid))
		return (1);
	return ((*env)->exit_status = execute_waitpid(pid, env));
}
