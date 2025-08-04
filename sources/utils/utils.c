/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:29:33 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/21 11:43:54 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	is_redir(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || \
		ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

void	print_syntax_error(char *token)
{
	if (!token)
		return ;
	ft_putstr_fd("minishell: syntax error near unexpected token "\
		, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
