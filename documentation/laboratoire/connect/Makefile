# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 17:23:40 by yzaoui            #+#    #+#              #
#    Updated: 2024/07/27 00:15:27 by yzaoui           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# pour dire que la cible ne sagit pas de nom fichier
.PHONY: all re clean fclean val test

############### OBJ du projet test execve

SERVER_FILES = server_example.cpp
CLIENT_FILES = client_example.cpp

OBJ_PATH = obj/

SERVER_OBJ = ${addprefix ${OBJ_PATH}, ${SERVER_FILES:.cpp=.o}}
CLIENT_OBJ = ${addprefix ${OBJ_PATH}, ${CLIENT_FILES:.cpp=.o}}

############### ligne de commande

RM = rm -rf
CC = c++
C_FLAGS = -std=c++98 -Wall -Wextra -Werror -g3

SERVER_NAME = server_example.out
CLIENT_NAME = client_example.out

############### COMMANDE OBLIGATOIRE

all: ${OBJ_PATH} ${SERVER_NAME} ${CLIENT_NAME}

${SERVER_NAME}: ${SERVER_OBJ}
	${CC} ${C_FLAGS} ${SERVER_OBJ} -o ${SERVER_NAME}

${CLIENT_NAME}: ${CLIENT_OBJ}
	${CC} ${C_FLAGS} ${CLIENT_OBJ} -o ${CLIENT_NAME}

$(OBJ_PATH)%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	$(RM) $(OBJ_PATH)
	rm -f output.txt

fclean: clean
	$(RM) ${SERVER_NAME} ${CLIENT_NAME}

re: fclean all

test: all
	./${SERVER_NAME} & \
	sleep 1 && \
	./${CLIENT_NAME}

val: all
	valgrind ./${CLIENT_NAME}
