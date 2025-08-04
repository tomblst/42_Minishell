/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:08:02 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 14:30:05 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_end_of_pipe(int *status, pid_t pid1, pid_t pid2, t_env **env)
{
	g_signal_status = 1;
	waitpid(pid1, &status[0], 0);
	waitpid(pid2, &status[1], 0);
	handle_child_signal(status[0], env);
	handle_child_signal(status[1], env);
	if (!WIFEXITED(status[1]) && !WIFSIGNALED(status[1]))
		(*env)->exit_status = 1;
	g_signal_status = 0;
}

void	execute_pipe(t_ast *ast, int old_in, int old_out, t_ast *ast_init)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		status[2];

	status[0] = ((status[1] = 0));
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"));
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"));
	if (pid1 == 0)
		h_child_process(ast->left, pipe_fd, STDOUT_FILENO, ast_init);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork"));
	if (pid2 == 0)
		h_child_process(ast->right, pipe_fd, STDIN_FILENO, ast_init);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	handle_end_of_pipe(status, pid1, pid2, &(ast_init->env));
	if (!WIFEXITED(status[1]) && !WIFSIGNALED(status[1]))
		ast_init->env->exit_status = 1;
	restore_dup(old_in, old_out);
}

void	h_child_process(t_ast *ast, int pipe_fd[2], int std_fd, t_ast *ast_init)
{
	reset_signals_for_child();
	if (std_fd == STDOUT_FILENO)
		close(pipe_fd[0]);
	else
		close(pipe_fd[1]);
	if (std_fd == STDOUT_FILENO)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	execute_ast(ast, ast_init);
	free_ast_fork(ast_init);
	rl_clear_history();
	exit(0);
}

void	resolve_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	cmd->is_builtin = is_builtin(cmd->args[0]);
	if (!cmd->is_builtin)
	{
		cmd->path = get_command_path(cmd->args[0], *env);
		if (!cmd->path)
		{
			printf("minishell: %s: command not found\n", cmd->args[0]);
			(*env)->exit_status = 127;
			return ;
		}
	}
	else
		cmd->path = NULL;
}
