C		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a
SRCS = $(wildcard *.c)
OBJS	= ${SRCS:.c=.o}
RM		= rm -f
all: ${NAME}
%.o: %.c libft.h	
	${C} ${CFLAGS} -c $< -o $@
${NAME}: ${OBJS}
	ar -rc $@ ${OBJS}
clean:
	${RM} ${OBJS}
fclean:	clean
	${RM} ${NAME}
re:	fclean all
.PHONY:	all clean fclean re
