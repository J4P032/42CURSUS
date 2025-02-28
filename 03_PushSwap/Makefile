CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = push_swap
LIBRARY = ./libft/libft.a
SRC = main.c stack.c ps_atol.c move_swap.c move_push.c checker_value.c move_rotate.c \
counting_sort.c ksort.c ft_sqrt.c ordering_distribution.c brute_force.c moves_counter.c \
moves_counter2.c normal_short.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(NAME)

$(LIBRARY):
	@make -C libft

%.o: %.c push_swap.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBRARY)
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all re clean fclean
