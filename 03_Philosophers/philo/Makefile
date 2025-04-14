CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread -pthread
NAME = philo
INCLUDES = philo.h
SRC = ft_calloc.c philo.c ft_atol.c free.c threads.c threads_2.c atomic.c
OBJS = $(SRC:.c=.o)
RM = rm -rf

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(INCLUDES)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean

	
