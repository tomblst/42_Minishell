/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:26:31 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/28 16:31:37 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_a_ty type, t_cmd *cmd)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	node->filename = NULL;
	node->env = NULL;
	node->env_array = NULL;
	return (node);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	free_cmd(ast->cmd);
	free(ast->filename);
	free(ast);
}

void	free_ast_fork(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	free_cmd(ast->cmd);
	free_env_list(ast->env);
	free(ast->filename);
	free(ast);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if ((cmd)->args)
	{
		i = 0;
		while ((cmd)->args[i])
		{
			free((cmd)->args[i]);
			i++;
		}
		free((cmd)->args);
	}
	if ((cmd)->path)
		free((cmd)->path);
	free(cmd);
}

char	**ft_realloc(char **ptr, size_t old_size, size_t new_size)
{
	char	**new_ptr;
	size_t	i;

	i = 0;
	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = malloc(sizeof(char *) * new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		while (i < (old_size / sizeof(char *)))
		{
			new_ptr[i] = ptr[i];
			i++;
		}
	}
	while (i < (new_size / sizeof(char *)))
	{
		new_ptr[i] = NULL;
		i++;
	}
	return (free(ptr), new_ptr);
}
