/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:07:13 by vflores           #+#    #+#             */
/*   Updated: 2025/03/25 15:41:49 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_env *env)
{
	t_env	*current;
	int		shlvl;

	current = env;
	shlvl = 0;
	while (current)
	{
		if (ft_strncmp(current->key, "SHLVL", 5) == 0)
		{
			shlvl = ft_atoi(current->value);
			shlvl++;
			free(current->value);
			current->value = ft_itoa(shlvl);
			return ;
		}
		current = current->next;
	}
}

t_env	*init_env_node(char *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	new->key = ft_substr(str, 0, i);
	if (!new->key)
		return (free(new), NULL);
	if (str[i] == '=')
		new->value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	else
		new->value = ft_strdup("");
	if (!new->value && str[i] == '=')
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->is_exported = 0;
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **env, int argc, char **argv)
{
	t_env	*lst_env;
	t_env	*init;
	t_env	*new;
	int		i;

	(void)argc;
	(void)argv;
	if (!env || !env[0])
		return (init_no_env());
	lst_env = init_env_node(env[0]);
	i = 1;
	if (!lst_env)
		return (NULL);
	init = lst_env;
	while (env[i])
	{
		new = init_env_node(env[i]);
		if (!new)
			return (free_env_list(lst_env), NULL);
		init->next = new;
		init = new;
		i++;
	}
	update_shlvl(lst_env);
	return (lst_env);
}

/* fonction pour free la liste d'environemment.*/
void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
