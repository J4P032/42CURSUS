CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer # -O1
# valgrind --track-fds==yes
NAME = minishell
LIBFT = ./libft/libft.a
SRC = 	src/main.c \
		src/history_m.c \
		src/clean_all_m.c \
		src/bi_pwd_m.c \
		src/bi_env_m.c \
		src/bi_echo_m.c \
		src/bi_export_m.c \
		src/signal_j.c \
		src/bi_cd_m.c \
		src/bi_unset_m.c \
		src/execute_command_m.c \
		src/manage_inputs_m.c \
		src/manage_inputs_utils_j.c
OBJDIR = obj
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
RM	= rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) inc/minishell_j.h inc/minishell_m.h
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lreadline -o $(NAME)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all re clean fclean
