CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = server
LIBRARY = ./ft_printf/libftprintf.a
SRC =  main.c
OBJS = $(SRC:.c=.o)

RM	= rm -rf

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	@make -C ft_printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBRARY)
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
