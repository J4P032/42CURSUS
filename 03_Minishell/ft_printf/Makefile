CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libftprintf.a
LIBRARY = ../libft/libft.a
SRC = ft_printf.c ft_printf_flag_type.c ft_printf_other_flags.c
OBJS = $(SRC:.c=.o)
RM	= rm -rf

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	make -C ../libft

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -I../libft -c $< -o $@

$(NAME): $(OBJS) $(LIBRARY)
	ar -rc $@ $(OBJS)
	ar -x $(LIBRARY) # Extrae los objetos de libft.a
	ar -rc $@ *.o # Añade los objetos a libftprintf.a
	ar -s $@ # Indexa la librería
	rm -f *.o

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
