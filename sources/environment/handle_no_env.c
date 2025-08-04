/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:38:16 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/25 15:45:21 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_pwd_node(void)
{
	t_env	*pwd_node;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	pwd_node = malloc(sizeof(t_env));
	if (!pwd_node)
		return (free(cwd), NULL);
	pwd_node->key = ft_strdup("PWD");
	pwd_node->value = ft_strdup(cwd);
	free(cwd);
	if (!pwd_node->key || !pwd_node->value)
		return (free(pwd_node->key), \
		free(pwd_node->value), free(pwd_node), NULL);
	pwd_node->is_exported = 1;
	pwd_node->next = NULL;
	return (pwd_node);
}

static t_env	*create_shlvl_node(void)
{
	t_env	*shlvl_node;

	shlvl_node = malloc(sizeof(t_env));
	if (!shlvl_node)
		return (NULL);
	shlvl_node->key = ft_strdup("SHLVL");
	shlvl_node->value = ft_strdup("1");
	if (!shlvl_node->key || !shlvl_node->value)
		return (free(shlvl_node->key), free(shlvl_node->value), \
		free(shlvl_node), NULL);
	shlvl_node->is_exported = 1;
	shlvl_node->next = NULL;
	return (shlvl_node);
}

static t_env	*create_underscore_node(void)
{
	t_env	*underscore_node;

	underscore_node = malloc(sizeof(t_env));
	if (!underscore_node)
		return (NULL);
	underscore_node->key = ft_strdup("_");
	underscore_node->value = ft_strdup("/usr/bin/env");
	if (!underscore_node->key || !underscore_node->value)
		return (free(underscore_node->key), \
		free(underscore_node->value), free(underscore_node), NULL);
	underscore_node->is_exported = 1;
	underscore_node->next = NULL;
	return (underscore_node);
}

t_env	*init_no_env(void)
{
	t_env	*pwd_node;
	t_env	*shlvl_node;
	t_env	*underscore_node;

	pwd_node = create_pwd_node();
	if (!pwd_node)
		return (NULL);
	shlvl_node = create_shlvl_node();
	if (!shlvl_node)
		return (free_env_list(pwd_node), NULL);
	underscore_node = create_underscore_node();
	if (!underscore_node)
		return (free_env_list(pwd_node), free_env_list(shlvl_node), NULL);
	pwd_node->next = shlvl_node;
	shlvl_node->next = underscore_node;
	return (pwd_node);
}
