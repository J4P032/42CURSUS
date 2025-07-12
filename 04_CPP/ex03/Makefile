CXX = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -Wshadow

NAME = a.out
HEADERS =	AMateria.hpp \
			IMateriaSource.hpp \
			MateriaSource.hpp \
			ICharacter.hpp \
			Character.hpp \
			Cure.hpp \
			Ice.cpp
SRC =		main.cpp \
			AMateria.cpp \
			IMateriaSource.cpp \
			MateriaSource.cpp \
			ICharacter.cpp \
			Character.cpp \
			Cure.cpp \
			Ice.cpp 
			
OBJDIR = obj
OBJS = $(SRC:%.cpp=$(OBJDIR)/%.o)
RM	= rm -rf

all: $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	@$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
