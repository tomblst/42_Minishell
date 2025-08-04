/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:34:35 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 14:44:40 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

static int	validate_quotes(const char *input)
{
	int	i;
	int	state;

	i = 0;
	state = QUOTE_NONE;
	while (input[i])
	{
		update_quote_state(input[i], &state);
		i++;
	}
	if (state != QUOTE_NONE)
		return (0);
	return (1);
}

void	init_ast_env_array(t_ast *ast, char **environement, t_env **env)
{
	if (!ast)
		return ;
	ast->env_array = environement;
	ast->env = *env;
	init_ast_env_array(ast->left, environement, env);
	init_ast_env_array(ast->right, environement, env);
}

int	process_line(char *line, t_env **env, char **environement)
{
	t_token	*tokens;
	t_ast	*ast;

	if (!validate_quotes(line))
		return (printf("minishell: syntax error: unmatched quote\n"), 0);
	tokens = tokenize(line);
	if (!check_syntax(tokens))
		return (free_tokens(tokens), (*env)->exit_status = 2, 1);
	if (!tokens)
		return (1);
	ast = parse_token(tokens);
	free_tokens(tokens);
	if (!ast)
	{
		printf("Parsing failed\n");
		return ((*env)->exit_status = 1, 1);
	}
	init_ast_env_array(ast, environement, env);
	execute_ast(ast, ast);
	free_ast(ast);
	return (0);
}

int	main(int argc, char **argv, char **environement)
{
	char	*line;
	t_env	*env;

	setup_signals();
	env = init_env(environement, argc, argv);
	while (1)
	{
		line = readline("minishell$ ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
		if (!line)
		{
			free(line);
			printf("exit\n");
			break ;
		}
		g_signal_status = 0;
		if (ft_strlen(line) != 0)
			process_line(line, &env, environement);
		free(line);
	}
	free_env_list(env);
	rl_clear_history();
	return (0);
}
