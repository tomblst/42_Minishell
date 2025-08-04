/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:43:08 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/25 13:14:09 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Gets the value of an environment variable
** Example: OLDPWD
** Value of OLDPWD = "/home/vflores/Cursus/Minishell"
*/
char	*get_env_value(t_env *env, const char *var_name)
{
	t_env	*current;

	if (!env || !var_name || !*var_name)
		return (NULL);
	current = env;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, var_name) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			else
				return (NULL);
		}
		current = current->next;
	}
	return (NULL);
}

void	process_variable(t_result *res, const char *arg, int *i,
	t_env *env)
{
	char	var_name[256];
	char	*value;
	int		k;

	k = 0;
	ft_memset(var_name, 0, sizeof(var_name));
	while ((ft_isalpha(arg[*i]) || arg[*i] == '_') && k < 255)
		var_name[k++] = arg[(*i)++];
	value = get_env_value(env, var_name);
	if (value)
	{
		k = 0;
		while (value[k] && res->j < 1023)
			res->result[res->j++] = value[k++];
	}
	free(value);
}

void	safe_replace(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
}
