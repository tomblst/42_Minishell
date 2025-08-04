/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:52 by tbellest          #+#    #+#             */
/*   Updated: 2025/03/31 12:37:23 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <ctype.h>
# include "libft.h"

/* Variable globales */
extern int	g_signal_status;

# define QUOTE_NONE 0
# define QUOTE_SINGLE 1
# define QUOTE_DOUBLE 2
# define MAX_EXPANSION_SIZE 4096

//***structures token***

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_token_type	quote_type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_exported;
	int				exit_status;
	struct s_env	*next;
}	t_env;

//***structures command***

typedef struct s_cmd
{
	char			**args;
	char			*path;
	int				is_builtin;
	int				quote_state;
	struct s_cmd	*next;
}	t_cmd;

//***structures ast***

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_APPEND,
	AST_HEREDOC,
	AST_ERROR,
}	t_a_ty;

typedef struct s_ast
{
	t_a_ty			type;
	t_cmd			*cmd;
	t_env			*env;
	char			**env_array;
	char			*filename;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_result
{
	char	*result;
	int		j;
	int		i;
}	t_result;

/******Expander*****/

/* Expander core functions (expander_core.c) */
char	*expand_variable_with_quotes(const char *input, t_env *env);
char	*expand_variable(const char *arg, t_env *env);
void	expand_command(t_cmd *cmd, t_env *env);
int		process_dollar(const char *input, t_env *env, t_result *res, int *i);
void	process_question_mark(char *result, int *j, int *i, t_env *env);

/* Expander environment functions (expander_env.c) */
char	*get_env_value(t_env *env, const char *var_name);
void	process_variable(t_result *res, const char *arg, int *i, t_env *env);
void	safe_replace(char **old, char *new);

/* Expander quote handling functions (expander_quote.c) */
char	*strip_quotes(const char *input);
int		is_opening_or_closing_quote(char c, int state);
void	process_quote_state(char c, int *state);
void	update_quote_state(char c, int *state);
int		should_copy_char(char c, int *state);

// Initialisation de l'environnement
t_env	*init_env_node(char *str);
t_env	*init_env(char **env, int argc, char **argv);
void	free_env_list(t_env *head);
void	print_env(t_env *env);
t_env	*init_no_env(void);

//print_sort_env
void	print_sorted_env(t_env *env);

//***token***

// tokenizer
t_token	*tokenize(char *line);

// token utils
t_token	*new_token(t_token_type type, char *value);
void	add_token(t_token **token, char *value, t_token_type type);
int		ft_isspace(char c);
int		is_operator(char c);

// token debug
void	print_tokens(t_token *token);
void	free_tokens(t_token *token);
int		check_syntax(t_token *token);

//***parse***

// ast
t_ast	*parse_token(t_token *current);
t_ast	*parse_t_pipe(t_token **cur, t_ast **ast, t_cmd **cmd, int *a_count);
t_ast	*parse_t_redir(t_token **cur, t_ast **ast, t_cmd **cmd, int *a_count);
t_ast	*create_redirection_node(t_token *current);
void	parse_token_word(t_token *current, t_cmd **cmd, int *args_count);

// ast utils
t_ast	*new_ast_node(t_a_ty type, t_cmd *cmd);
void	free_ast(t_ast *ast);
void	free_ast_fork(t_ast *ast);
void	free_cmd(t_cmd *cmd);
char	**ft_realloc(char **ptr, size_t old_size, size_t new_size);
t_cmd	*new_cmd(void);
t_a_ty	token_to_ast_type(t_token_type token_type);

//***builtins***

// builtins utils
int		is_builtin(char *cmd);
int		ft_cd(t_env **env, char **args);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(char **args, t_env *env);
int		ft_export(t_env **env, char **args);
int		ft_unset(t_env **env, char **args);
int		ft_exit(char **args, t_ast *ast, t_env **env);
int		is_valid_variable_name(char *name);

t_env	*find_env_var(t_env *env, const char *key);
void	add_env_var(t_env **env, char *key, char *value, int is_exported);
void	remove_env_var(t_env **env, const char *key);

//***executors***

// find command path
char	*get_command_path(char *cmd, t_env *env);
char	*find_path_env(t_env *env);
char	*search_command_in_path(char *cmd, char **directories);

// execute command (execute_comand.c)
int		execute_command(t_ast *ast, t_env **env);
int		execute_builtin(t_env **env, char **args, t_ast *ast);

// execute ast (execute_ast.c)
int		execute_ast(t_ast *ast, t_ast *ast_init);
void	resolve_cmd(t_cmd *cmd, t_env **env);
void	restore_dup(int old_in, int old_out);

// execute pipe (execute_pipe.c)
void	execute_pipe(t_ast *ast, int old_in, int old_out, t_ast *ast_init);
void	h_child_process(t_ast *ast, int *pipe_fd, int fd, t_ast *ast_init);

// execute redirections (execute_redirections.c)
void	execute_redirection(t_ast *ast, int old_in, int old_out, int mode);
char	*execute_redir_heredoc(char *delimiter);
void	handle_redir_heredoc(t_ast *ast, int old_in, int old_out);

// ***utils***

// utils
void	free_split(char **split);
int		is_redir(char *str);
void	print_ast(t_ast *ast, int level);
void	print_syntax_error(char *token);

//check syntax
int		check_syntax(t_token *token);

//signal
void	handle_sigint(int code);
void	setup_signals(void);
void	reset_signals_for_child(void);
void	handle_child_signal(int status, t_env **env);

#endif
