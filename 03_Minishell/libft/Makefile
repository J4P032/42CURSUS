CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_strtrim.c ft_putchar_fd.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_striteri.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
	ft_utoa.c ft_putnbr_base.c ft_strcmp.c ft_matrix_free.c ft_matrix_dup.c \
	ft_split_quotes.c ft_split_quotes_separator.c ft_split_quotes_words.c \
	ft_split_quotes_utils.c ft_split_quotes_separator2.c ft_strchr_quotes.c \
	ft_strcat.c ft_strcspn.c ft_atol.c ft_first_word.c ft_last_str.c \
	ft_matrix_len.c ft_input_free.c

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf

all: ${NAME}

%.o: %.c libft.h
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@ar -rc $@ ${OBJS}

clean:
	@${RM} ${OBJS}

fclean:	clean
	@${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
