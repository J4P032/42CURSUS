CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
LIBRARY = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRC = so_long.c window.c sprite.c keys.c frame.c get_next_line.c get_next_line_utils.c \
map.c map_2.c map_3.c sprite_pacman.c sprite_map.c frame_map.c pixels.c pacman_movement.c \
sprite_collect.c frame_collect.c time.c sprite_exit.c frame_exit.c
SRC2 = count_movements.c
SRCS_BONUS = count_movements_bonus.c
OBJS = $(SRC:.c=.o)
OBJS2 = $(SRC2:.c=.o)
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
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS2) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)

bonus: .bonus

.bonus: ${OBJS} ${OBJS_BONUS} $(LIBRARY) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)
	touch .bonus

clean:
	@$(RM) $(OBJS) $(OBJS2) ${OBJS_BONUS} .bonus
	@make clean -C libft
	@make clean -C minilibx-linux

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@make clean -C minilibx-linux

re: fclean all

.PHONY: all re clean fclean bonus
