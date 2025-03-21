# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 20:20:53 by smlamali          #+#    #+#              #
#    Updated: 2025/03/20 21:05:20 by smlamali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = Bot.cpp main.cpp Actions.cpp

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

NAME = bot

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all