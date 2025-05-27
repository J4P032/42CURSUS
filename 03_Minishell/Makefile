CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer # -O1
# valgrind --track-fds==yes
NAME = minishell
LIBFT = ./libft/libft.a
LIBFTPRINTF = ./ft_printf/libftprintf.a
SRC = 	src/main.c \
		src/history_m.c \
		src/clean_all_m.c \
		src/bi_pwd_m.c \
		src/bi_env_m.c \
		src/bi_env_dollar_j.c \
		src/bi_echo_short_j.c \
		src/bi_echo_m.c \
		src/bi_echo_dollar_j.c \
		src/bi_export_m.c \
		src/signal_j.c \
		src/bi_cd_m.c \
		src/bi_unset_m.c \
		src/execute_command_m.c \
		src/manage_inputs_m.c \
		src/manage_inputs_utils_j.c \
		src/manage_input_dollars_j.c \
		src/manage_input_dollars2_j.c \
		src/redirections_m.c \
		src/bi_exit_j.c \
		src/redirections_heredoc_m.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/parsing_j.c \
		src/manage_token_parsing_j.c \
		src/manage_token_dollars_j.c \
		src/manage_token_dollars2_j.c \
		src/manage_pipes_m.c \
		src/realloc_input_j.c \
		src/split_exp_utils_j.c
OBJDIR = obj
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
RM	= rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C ft_printf

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(LIBFTPRINTF) inc/minishell_j.h inc/minishell_m.h
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./ft_printf -lftprintf -lreadline -o $(NAME)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all

.PHONY: all re clean fclean
