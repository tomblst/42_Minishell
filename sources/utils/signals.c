/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:05:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 14:30:56 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_signal_status == 0)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		setup_signals();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_child_signal(int status, t_env **env)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(2, "\n", 1);
		}
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		if (env && *env)
			(*env)->exit_status = sig + 128;
	}
	else if (WIFEXITED(status))
		(*env)->exit_status = WEXITSTATUS(status);
	else
		(*env)->exit_status = 1;
}
