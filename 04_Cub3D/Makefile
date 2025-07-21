CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBRARY = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRC =  
SRCS_BONUS = 
OBJS = $(SRC:.c=.o)
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
RM	= rm -rf
all: $(NAME)

$(LIBRARY):
	@make -C libft

$(MINILIBX):
	@make -C minilibx-linux

%.o: %.c so_long.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJS2) $(LIBRARY) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)

bonus: .bonus

.bonus: ${OBJS} ${OBJS_BONUS} $(LIBRARY) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME_BONUS)
	touch .bonus

clean:
	@$(RM) $(OBJS) ${OBJS_BONUS} .bonus
	@make clean -C libft
	@make clean -C minilibx-linux

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -C libft
	@make clean -C minilibx-linux

re: fclean all

.PHONY: all re clean fclean bonus
