/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:23:32 by vflores           #+#    #+#             */
/*   Updated: 2025/03/24 16:45:24 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_var_update(t_env **env, char *key, char *value)
{
	t_env	*var;

	var = find_env_var(*env, key);
	if (var)
	{
		free(var->value);
		var->value = value;
		var->is_exported = 0;
	}
	else
	{
		if (!value)
			value = ft_strdup("");
		add_env_var(env, key, value, 0);
		free(value);
	}
	free(key);
}

static void	process_var_with_value(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal_sign - arg);
	if (!is_valid_variable_name(key))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(key);
		(*env)->exit_status = 1;
		return ;
	}
	value = ft_strdup(equal_sign + 1);
	handle_var_update(env, key, value);
}

static void	process_var_without_value(t_env **env, char *key)
{
	t_env	*var;

	if (!is_valid_variable_name(key))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		(*env)->exit_status = 1;
		return ;
	}
	var = find_env_var(*env, key);
	if (!var)
		add_env_var(env, key, NULL, 1);
}

int	ft_export(t_env **env, char **args)
{
	int		i;
	char	*equal_sign;

	if (!args[1])
	{
		if (*env)
			print_sorted_env(*env);
		else
			ft_putstr_fd("export: no variables to show\n", STDERR_FILENO);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			process_var_with_value(env, args[i]);
		else
			process_var_without_value(env, args[i]);
		i++;
	}
	return (0);
}

int	is_valid_variable_name(char *name)
{
	if (!*name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
