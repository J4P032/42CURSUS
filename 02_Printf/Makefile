CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRC = ft_printf.c ft_printf_flag_type.c ft_putnbr_base.c  \
ft_utoa.c ft_itoa.c ft_strlen.c ft_strchr.c ft_calloc.c \
ft_bzero.c ft_printf_other_flags.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(NAME)

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rc $@ $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
