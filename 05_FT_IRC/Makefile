# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:05:02 by user1             #+#    #+#              #
#    Updated: 2026/02/05 16:50:18 by mvassall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX := c++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address
#CXXFLAGS := -Wall -Werror -Wextra -std=c++98
SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
RM := /bin/rm -f

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
#SRCS := main.cpp 
INCLUDES := $(shell find $(INCLUDE_DIR) -name '*.hpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

NAME = ircserv

.PHONY: all clean fclean re

all: $(NAME)

$(OBJS): $(INCLUDES)

$(BUILD_DIR)/%.cpp.o: %.cpp $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all
