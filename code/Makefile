# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 17:23:40 by yzaoui            #+#    #+#              #
#    Updated: 2025/03/02 17:26:38 by yzaoui           ###   ########.fr        #
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
		--read-var-info=yes \
		# --log-file=valgrind.log

PORT = 8080

MDP = mdp

############### OBJ du projet ircserv

ACTION_SERV_FILES =	cap.cpp				\
					disconnect.cpp		\
					error_recv_data.cpp	\
					idk.cpp				\
					invite.cpp			\
					join.cpp			\
					kick.cpp			\
					mode.cpp			\
					nick.cpp			\
					no_action.cpp		\
					ping.cpp			\
					privmsg.cpp			\
					quit.cpp			\
					shutdown.cpp		\
					topic.cpp			\
					user.cpp			\
					whois.cpp

OTHER_FILE_FROM_IRSSI_SERV =	./class/Irssi_serv/other/execution.cpp		\
								./class/Irssi_serv/other/other.cpp			\
								./class/Irssi_serv/other/errase_element.cpp	\
								./class/Irssi_serv/other/geter.cpp

CLASS_FILES =	./class/Server/Server.cpp				\
				./class/Cmd_irssi/Cmd_irssi.cpp			\
				./class/Irssi_serv/Irssi_serv.cpp		\
				${OTHER_FILE_FROM_IRSSI_SERV}			\
				./class/User/User.cpp					\
				./class/Client/Client.cpp				\
				./class/User/UserHuman/UserHuman.cpp	\
				./class/Channel/Channel.cpp				\
				${addprefix ./class/Irssi_serv/action_serv/, ${ACTION_SERV_FILES}}

UTILS_FILES =	./utils/define_array_and_get_element_of_array.cpp	\
				./utils/ft_utils.cpp								\
				./utils/affichage_utils.cpp

IRCSERV_SRC =	main.cpp						\
				message_to_mate_to_delete.cpp	\
				${UTILS_FILES}					\
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