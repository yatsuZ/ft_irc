/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:27:32 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/26 00:33:36 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./affichage.ipp"


int	main(int argc, char **argv)
{
	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);
	signal(SIGPIPE, SIG_IGN);

	std::cout << "---------------------------" << std::endl << std::endl;
	try
	{
		if (argc != 3 || !argv)
			throw Init_serv_error("Pas le bon nombre d'argument il en faut 2.");
		Irssi_serv test(argv[1], argv[2]);
		std::cout << test;
		test.exec();
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << NOCOLOR << std::endl;
		return (1);
	}
	return (0);
}

/*
cmd pour demarer le serveur avec valgrind:
valgrind --tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--log-file=valgrind.log \
		--track-fds=yes	 \
		--read-var-info=yes \
		./ircserv 8080 mdp

test a faire :

nc <ip> <port> <message>
	exemple :
	nc 127.0.0.1 8080 exit
*/


// /connect irc.libera.chat
// /rawlog open irc_raw.log
