/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:23:35 by vflores           #+#    #+#             */
/*   Updated: 2025/03/31 14:43:00 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_exit(t_ast *ast)
{
	free_ast_fork(ast);
	rl_clear_history();
	printf("exit\n");
}

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_ast *ast, t_env **env)
{
	int		exit_code;

	(void)env;
	exit_code = 0;
	if (args[1])
	{
		if (!ft_isnumber(args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			clear_exit(ast);
			exit(2);
		}
		else if (ft_isnumber(args[1]) && args[2])
			return (printf("exit\nminishell: exit: too many arguments\n"), 1);
		else if (args[2])
		{
			printf("minishell: exit: too many arguments\n");
			clear_exit(ast);
			exit(2);
		}
		exit_code = (ft_atoi(args[1]) % 256);
	}
	clear_exit(ast);
	exit(exit_code);
	return (0);
}
