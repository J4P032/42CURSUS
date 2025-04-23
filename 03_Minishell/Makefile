CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# -lreadline
NAME = minishell
LIBFT = ./libft/libft.a
SRC = 	src/main.c
OBJDIR = obj
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
RM	= rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) inc/minishell_j.h inc/minishell_m.h
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

clean:
	@$(RM) $(OBJDIR)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all re clean fclean
