/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:46:26 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/28 17:59:52 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Expand variables in a command argument
** Variable names must be alphanumeric or underscore
*/
char	*expand_variable(const char *arg, t_env *env)
{
	char		*result;
	int			i;
	t_result	res;

	result = ft_calloc(MAX_EXPANSION_SIZE, 1);
	if (!result)
		return (NULL);
	i = 0;
	res.j = 0;
	res.result = result;
	res.i = 0;
	while (arg[i] && res.j < 1023)
	{
		if (arg[i] == '$')
			process_dollar(arg, env, &res, &i);
		else
			res.result[res.j++] = arg[i++];
	}
	res.result[res.j] = '\0';
	return (res.result);
}

static void	remove_empty_args(t_cmd *cmd)
{
	int	i;
	int	j;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
		{
			cmd->args[j] = cmd->args[i];
			j++;
		}
		else
			free(cmd->args[i]);
		i++;
	}
	cmd->args[j] = NULL;
}

void	expand_command(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*expanded;
	char	*unquoted;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_variable_with_quotes(cmd->args[i], env);
		if (expanded)
		{
			safe_replace(&cmd->args[i], expanded);
			unquoted = strip_quotes(cmd->args[i]);
			if (unquoted)
				safe_replace(&cmd->args[i], unquoted);
		}
		i++;
	}
	remove_empty_args(cmd);
}

int	process_dollar(const char *input, t_env *env, t_result *res, int *i)
{
	int		expanded;
	char	quote;

	expanded = 1;
	(*i)++;
	if (input[*i] == '\0')
		return (res->result[res->j++] = '$', 1);
	if (input[*i] == '?')
		process_question_mark(res->result, &res->j, i, env);
	else if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[(*i)++];
		if (input[*i] == quote)
			(*i)++;
	}
	else if (ft_isalpha(input[*i]) || input[*i] == '_')
		process_variable(res, input, i, env);
	else
	{
		res->result[res->j++] = '$';
		if (input[*i])
			res->result[res->j++] = input[(*i)++];
	}
	return (expanded);
}

/*
** Process the $? special variable and add to result
*/
void	process_question_mark(char *result, int *j, int *i, t_env *env)
{
	char	*status;
	int		k;

	status = ft_itoa(env->exit_status);
	if (status)
	{
		k = 0;
		while (status[k] && *j < 1023)
			result[(*j)++] = status[k++];
		free(status);
	}
	(*i)++;
}
