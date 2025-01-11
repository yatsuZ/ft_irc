# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 17:23:40 by yzaoui            #+#    #+#              #
#    Updated: 2025/01/11 00:34:01 by yzaoui           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# pour dire que la cible ne sagit pas de nom fichier
.PHONY: all re clean fclean val test

############### POUR TESTER

VAL_CMD = valgrind --tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--log-file=valgrind.log \
		--read-var-info=yes

PORT = 8080

MDP = mdp

############### OBJ du projet ircserv

CLASS_FILES =	./class/Server/Server.cpp		\
				./class/Server/execution.cpp	\
				./class/Client/Client.cpp

UTILS_FILES =	./utils/color.cpp	\
				./utils/ft_utils.cpp

IRCSERV_SRC =	main.cpp		\
				${UTILS_FILES}	\
				${CLASS_FILES}

OBJ_PATH = obj/

PROG_OBJ = ${addprefix ${OBJ_PATH}, ${IRCSERV_SRC:.cpp=.o}}

############### ligne de commande

RM = rm -rf
CC = c++
C_FLAGS = -std=c++98 -Wall -Wextra -Werror -g3

PROGRAM_NAME = ircserv

############### COMMANDE OBLIGATOIRE

all: ${OBJ_PATH} ${PROGRAM_NAME}

${PROGRAM_NAME}: ${PROG_OBJ}
	${CC} ${C_FLAGS} ${PROG_OBJ} -o ${PROGRAM_NAME}

$(OBJ_PATH)%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	$(RM) $(OBJ_PATH)
	${RM} valgrind.log

fclean: clean
	$(RM) ${PROGRAM_NAME}

re: fclean all

test: all
	${VAL_CMD} ./${PROGRAM_NAME} ${PORT} ${MDP}

val: all
	valgrind ./${PROGRAM_NAME}