CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus
LIBFT = ./libft/libft.a
LIBFTPRINTF = ./ft_printf/libftprintf.a
SRC_SERVER =  server.c server_utils.c server_utils2.c
SRC_CLIENT = client.c client_utils.c
SRC_SERVER_BONUS = server_bonus.c server_utils_bonus.c server_utils2_bonus.c
SRC_CLIENT_BONUS = client_bonus.c client_utils_bonus.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
RM	= rm -rf

all: $(LIBFT) $(LIBFTPRINTF) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C ft_printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(LIBFTPRINTF) server.h
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(LIBFTPRINTF) client.h
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME_CLIENT)

bonus: .bonus

.bonus: ${OBJS_SERVER_BONUS} $(OBJS_CLIENT_BONUS) $(LIBFT) $(LIBFTPRINTF) client_bonus.h server_bonus.h
	@$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME_SERVER_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -L./libft -lft -L./ft_printf -lftprintf -o $(NAME_CLIENT_BONUS)
	touch .bonus

clean:
	@$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS) .bonus
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all

.PHONY: all re clean fclean bonus
