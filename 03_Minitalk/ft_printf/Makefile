CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libftprintf.a
LIBRARY = ../libft/libft.a
SRC = ft_printf.c ft_printf_flag_type.c ft_printf_other_flags.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	make -C libft

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rc $@ $(OBJS)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all re clean fclean
