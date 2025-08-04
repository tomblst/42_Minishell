/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:06:47 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 11:07:55 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_heredoc(t_ast *ast, int old_in, int old_out)
{
	int	fd;

	fd = open(ast->filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open heredoc");
		ast->env->exit_status = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (ast->right)
		execute_ast(ast->right, ast);
	else if (ast->left)
		execute_ast(ast->left, ast);
	unlink(ast->filename);
	restore_dup(old_in, old_out);
}

static char	*generate_heredoc_filename(void)
{
	static int	here_doc_count;
	char		*count;
	char		*filename;

	count = ft_itoa(here_doc_count++);
	if (!count)
		return (perror("ft_itoa"), NULL);
	filename = ft_strjoin("/tmp/heredoc_tmp", count);
	free(count);
	if (!filename)
		return (perror("ft_strjoin"), NULL);
	return (filename);
}

char	*execute_redir_heredoc(char *delimiter)
{
	int		fd;
	char	*filename;
	char	*line;

	filename = generate_heredoc_filename();
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open heredoc"), free(filename), NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (filename);
}

void	execute_redirection(t_ast *ast, int old_in, int old_out, int mode)
{
	int		fd;

	if (mode == O_RDONLY)
		fd = open(ast->filename, mode);
	else
		fd = open(ast->filename, mode, 0644);
	if (fd == -1)
		return (ast->env->exit_status = 1, perror(ast->filename));
	if (!ast->left)
		return (close(fd), restore_dup(old_in, old_out));
	if (mode == O_RDONLY)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	execute_ast(ast->left, ast);
	restore_dup(old_in, old_out);
}
