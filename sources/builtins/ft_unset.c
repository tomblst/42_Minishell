/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:23:25 by vflores           #+#    #+#             */
/*   Updated: 2025/03/24 13:17:26 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env **env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(env, args[i]);
		if (ft_strcmp(args[i], "PATH") == 0)
		{
			remove_env_var(env, "XDG_SESSION_PATH");
			remove_env_var(env, "XDG_SEAT_PATH");
			remove_env_var(env, "LD_LIBRARY_PATH");
		}
		i++;
	}
	return (0);
}
