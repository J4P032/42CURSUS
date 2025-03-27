CC = cc
CFLAGS = -g
NAME = server
LIBFT = ./libft/libft.a
LIBFTPRINTF = ./ft_printf/libftprintf.a
SRC =  main.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(LIBFT) $(LIBFTPRINTF) $(NAME)

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C ft_printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(LIBFTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all

.PHONY: all re clean fclean
