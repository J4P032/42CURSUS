CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME_SERVER = server
NAME_CLIENT = client
LIBFT = ./libft/libft.a
LIBFTPRINTF = ./ft_printf/libftprintf.a
SRC_SERVER =  server.c
SRC_CLIENT = client.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
RM	= rm -rf

all: $(LIBFT) $(LIBFTPRINTF) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C ft_printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(LIBFTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(LIBFTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME_CLIENT)

clean:
	@$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT) 
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all

.PHONY: all re clean fclean
