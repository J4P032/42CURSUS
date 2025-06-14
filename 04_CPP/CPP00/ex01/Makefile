CXX = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = phonebook
HEADERS = 	PhoneBook.hpp \
			Contact.hpp \
			phonebook.hpp
SRC =	PhoneBook.cpp \
		Contact.cpp \
		main.cpp \
		phonebook_add.cpp
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
