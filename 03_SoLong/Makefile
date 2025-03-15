CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = so_long
LIBRARY = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRC = so_long.c window.c sprite.c keys.c frame.c get_next_line.c get_next_line_utils.c \
map.c map_2.c sprite_pacman.c sprite_map.c
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
