CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3D
NAME_BONUS = cub3D_bonus
LIBRARY = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx.a
SRC = 			main.c \
				window.c \
				map_2.c \
				map_3.c \
				map_4.c \
				map_5.c \
				map_6.c \
				get_next_line.c \
				get_next_line_utils.c \
				raycast.c \
				raycast_2.c \
				pixels.c \
				movement.c \
				keys.c \
				menu_keys.c \
				rotation.c \
				jump.c \
				sprite_draw.c \
				floor_ceiling.c
SRC_NOBONUS =	sprite.c \
				frame.c \
				map.c
SRC_BONUS =		sprite_bonus.c \
				frame_bonus.c \
				minimap_bonus.c \
				door_bonus.c \
				raycast_door.c \
				raycast_door_2.c \
				map_bonus.c \
				enemy_bonus2.c \
				enemy_bonus.c
OBJS = $(SRC:.c=.o)
OBJS_NOBONUS = ${SRC_NOBONUS:.c=.o}
OBJS_BONUS = ${SRC_BONUS:.c=.o}
RM	= rm -rf
all: $(NAME)

$(LIBRARY):
	@make -C libft

$(MINILIBX):
	@make -C minilibx-linux

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJS_NOBONUS) $(LIBRARY) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_NOBONUS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)

bonus: .bonus

.bonus: ${OBJS} ${OBJS_BONUS} $(LIBRARY) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) -L./libft -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME_BONUS)
	touch .bonus

clean:
	@$(RM) $(OBJS) $(OBJS_NOBONUS) $(OBJS_BONUS) .bonus
	@make clean -C libft
	@make clean -C minilibx-linux

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -C libft
	@make clean -C minilibx-linux

re: fclean all

rebonus: fclean bonus

.PHONY: all re clean fclean bonus rebonus
