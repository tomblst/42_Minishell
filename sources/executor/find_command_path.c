/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:06:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 14:44:51 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char *cmd, t_env *env)
{
	char		*path_env;
	char		**directories;
	char		*cmd_path;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = find_path_env(env);
	if (!path_env)
		return (NULL);
	directories = ft_split(path_env, ':');
	free(path_env);
	if (!directories)
		return (ft_putstr_fd("Error malloc PATH directories", 2), NULL);
	cmd_path = search_command_in_path(cmd, directories);
	free_split(directories);
	return (cmd_path);
}

char	*find_path_env(t_env *env)
{
	char	*value;

	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = ft_strdup(env->value);
			if (!value)
				return (NULL);
			return (value);
		}
		env = env->next;
	}
	return (ft_strdup(getenv("PATH")));
}

char	*search_command_in_path(char *cmd, char **directories)
{
	char	*full_path;
	char	*cmd_path;
	int		i;

	i = 0;
	while (directories[i])
	{
		full_path = ft_strjoin(directories[i], "/");
		if (!full_path)
			return (NULL);
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
