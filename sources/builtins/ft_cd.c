/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:22:39 by vflores           #+#    #+#             */
/*   Updated: 2025/03/24 17:07:32 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(t_env *env, char **args, int *print_path)
{
	t_env	*home_value;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home_value = find_env_var(env, "HOME");
		if (!home_value || !home_value->value)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (home_value->value);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		home_value = find_env_var(env, "OLDPWD");
		if (!home_value || !home_value->value || !home_value->value[0])
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		*print_path = 1;
		return (home_value->value);
	}
	return (args[1]);
}

static int	initialize_pwd_and_oldpwd(t_env **env)
{
	char	cwd[PATH_MAX];
	t_env	*oldpwd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		add_env_var(env, "PWD", cwd, 1);
		oldpwd = find_env_var(*env, "OLDPWD");
		if (!oldpwd)
			add_env_var(env, "OLDPWD", "", 1);
		return (0);
	}
	else
		return (ft_putstr_fd("cd: PWD not set\n", STDERR_FILENO), 1);
}

static int	update_oldpwd(t_env **env)
{
	t_env	*oldpwd;
	t_env	*pwd_value;

	pwd_value = find_env_var(*env, "PWD");
	if (!pwd_value)
		return (initialize_pwd_and_oldpwd(env));
	oldpwd = find_env_var(*env, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(pwd_value->value);
	}
	else
		add_env_var(env, "OLDPWD", pwd_value->value, 1);
	return (0);
}

static int	update_pwd(t_env **env, char *cwd)
{
	t_env	*pwd;

	pwd = find_env_var(*env, "PWD");
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	else
		add_env_var(env, "PWD", cwd, 0);
	return (0);
}

int	ft_cd(t_env **env, char **args)
{
	char	*path;
	char	cwd[PATH_MAX];
	int		print_path;

	print_path = 0;
	if (args[2])
		return (printf("minishell: cd: too many arguments\n"), 1);
	path = get_cd_path(*env, args, &print_path);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	update_oldpwd(env);
	update_pwd(env, cwd);
	if (print_path)
		printf("%s\n", cwd);
	return (0);
}
