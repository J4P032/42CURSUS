CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = so_long
LIBRARY = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRC = so_long.c window.c pixels.c simple_geometry.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(NAME)

$(LIBRARY):
	@make -C libft

$(MINILIBX):
	@make -C minilibx-linux

%.o: %.c so_long.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBRARY) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C libft
	@make clean -C minilibx-linux

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@make clean -C minilibx-linux

re: fclean all

.PHONY: all re clean fclean
