NAME = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -Iinclude -Ilibft

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Liste manuelle des fichiers sources
SRCS = \
sources/main.c \
sources/builtins/builtins_list_utils.c \
sources/builtins/builtins_utils.c \
sources/builtins/ft_cd.c \
sources/builtins/ft_echo.c \
sources/builtins/ft_env.c \
sources/builtins/ft_exit.c \
sources/builtins/ft_export.c \
sources/builtins/ft_pwd.c \
sources/builtins/ft_unset.c \
sources/environment/handle_env.c \
sources/environment/print_sort_env.c \
sources/environment/handle_no_env.c \
sources/executor/execute_ast.c \
sources/executor/execute_comand.c \
sources/executor/execute_pipe.c \
sources/executor/execute_redirections.c \
sources/executor/find_command_path.c \
sources/expander/expander_core.c \
sources/expander/expander_var_quote.c \
sources/expander/expander_env.c \
sources/expander/expander_quote.c \
sources/parser/ast.c \
sources/parser/ast_redir.c \
sources/parser/ast_utils.c \
sources/parser/ast_utils2.c \
sources/token/token_debug.c \
sources/token/tokenizer.c \
sources/token/token_utils.c \
sources/utils/check_syntax.c \
sources/utils/signals.c \
sources/utils/utils.c

# Génère les objets depuis les sources
OBJS = $(SRCS:.c=.o)

# Compilation de tous les fichiers
all: $(NAME)

# Compilation finale du programme
$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

# Compilation des fichiers .o individuellement
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage objets
clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

# Nettoyage total
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

# Recompilation totale
re: fclean all

.PHONY: all clean fclean re
