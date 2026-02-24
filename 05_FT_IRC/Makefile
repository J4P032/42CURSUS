# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:05:02 by user1             #+#    #+#              #
#    Updated: 2026/02/23 16:18:23 by mvassall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX := c++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -pedantic #-g -fsanitize=address
SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
RM := /bin/rm -f

# 1. Añadimos el prefijo del directorio a los fuentes
SRCS := $(addprefix $(SRC_DIR)/, \
	answer_auth.cpp answer_kick.cpp answer_notice.cpp answer_pong.cpp \
	answer_show.cpp IRCChannel.cpp IRCMessage.cpp utils.cpp \
	answer_invite.cpp answer_mode.cpp answer_part.cpp answer_privmsg.cpp \
	answer_topic.cpp IRCClient.cpp IRCServ.cpp answer_join.cpp answer_names.cpp \
	answer_ping.cpp answer_quit.cpp answer_who.cpp IRCCommand.cpp main.cpp)

# 2. Añadimos el prefijo del directorio a los includes
INCLUDES := $(addprefix $(INCLUDE_DIR)/, \
	IRCChannel.hpp IRCClient.hpp IRCCommand.hpp IRCMessage.hpp IRCServ.hpp utils.hpp)

# Esto generará objetos como build/src/main.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

NAME = ircserv

.PHONY: all clean fclean re

all: $(NAME)

konfu: src/konfu.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# 3. La regla corregida para encontrar los .cpp dentro de SRC_DIR
$(BUILD_DIR)/%.cpp.o: %.cpp $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) konfu

re: fclean all
