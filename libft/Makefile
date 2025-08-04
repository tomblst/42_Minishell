NAME = libft.a

FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	   ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	   ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	   ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c  ft_itoa_base.c get_next_line.c \
	   ft_printf.c handle_char_string.c handle_integer.c handle_hex.c handle_pointeur.c ft_strcmp.c
#ft_utoa.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c ft_lstiter_bonus.c

OBJSB = $(BONUS:.c=.o)

OBJS = $(FILES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	@ ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJSB)
	@ ar rcs $(NAME) $(OBJS) $(OBJSB)

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
