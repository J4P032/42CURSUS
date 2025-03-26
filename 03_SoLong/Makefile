CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
NAME_BONUS = so_long_bonus
LIBRARY = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRC =  window.c keys.c get_next_line.c get_next_line_utils.c check_ber.c\
map_2.c sprite_pacman.c sprite_map.c frame_map.c pixels.c pacman_movement.c \
sprite_collect.c frame_collect.c time.c sprite_exit.c frame_exit.c
SRC2 = count_movements.c frame.c sprite.c so_long.c map.c map_3.c
SRCS_BONUS = so_long_bonus.c count_movements_bonus.c sprite_bonus.c sprite_phantom_bonus.c \
map_bonus.c frame_bonus.c frame_phantom_bonus.c so_long_ai_bonus.c frame_phantom2_bonus.c \
map_3_bonus.c pacman_survive_bonus.c
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
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME_BONUS)
	touch .bonus

clean:
	@$(RM) $(OBJS) $(OBJS2) ${OBJS_BONUS} .bonus
	@make clean -C libft
	@make clean -C minilibx-linux

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -C libft
	@make clean -C minilibx-linux

re: fclean all

.PHONY: all re clean fclean bonus
