/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sort_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:29:55 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 12:14:40 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(t_env *env, char **key)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (key[i])
	{
		temp = find_env_var(env, key[i]);
		if (temp)
		{
			if (temp->value)
				printf("export %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("export %s\n", temp->key);
		}
		i++;
	}
}

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*temp;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static char	**collect_env_keys(t_env *env, int count)
{
	char	**env_keys;
	t_env	*temp;
	int		i;

	env_keys = malloc(sizeof(char *) * (count + 1));
	if (!env_keys)
		return (NULL);
	temp = env;
	i = 0;
	while (temp)
	{
		env_keys[i] = temp->key;
		temp = temp->next;
		i++;
	}
	env_keys[i] = NULL;
	return (env_keys);
}

static void	sort_env_keys(char **env_keys, int count)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(env_keys[i], env_keys[i + 1]) > 0)
			{
				tmp = env_keys[i];
				env_keys[i] = env_keys[i + 1];
				env_keys[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_sorted_env(t_env *env)
{
	char	**env_keys;
	int		count;

	count = count_env_vars(env);
	if (count == 0)
		return ;
	env_keys = collect_env_keys(env, count);
	if (!env_keys)
		return ;
	sort_env_keys(env_keys, count);
	print_env_var(env, env_keys);
	free(env_keys);
}
