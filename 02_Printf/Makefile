CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libftprintf.a
LIBRARY = ./libft/libft.a
SRC = ft_printf.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(NAME) $(LIBRARY)

$(LIBRARY):
	make -C libft

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBRARY)
	ar -rc $@ $(OBJS) $(LIBRARY)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all
	make fclean -C libft

.PHONY: all re clean fclean
