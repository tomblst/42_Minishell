/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:23:24 by vflores           #+#    #+#             */
/*   Updated: 2025/03/21 12:15:43 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

void	add_env_var(t_env **env, char *key, char *value, int is_exported)
{
	t_env	*new_var;
	t_env	*last;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->is_exported = is_exported;
	new_var->next = NULL;
	if (!*env)
		*env = new_var;
	else
	{
		last = *env;
		while (last->next)
			last = last->next;
		last->next = new_var;
	}
}

void	remove_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		if (prev)
		{
			prev->next = current->next;
		}
		else
		{
			*env = current->next;
		}
		free(current->key);
		free(current->value);
		free(current);
	}
}
