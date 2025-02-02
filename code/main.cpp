/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:27:32 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 23:32:47 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./affichage.ipp"

void TO_DO(void)
{
	std::cout << BLUE << "SALUT ! Voici ce qu'il y a à faire." << NOCOLOR << std::endl;

	std::cout << "1. " << CYAN << "Faire l'interprétation des actions reçues du client irssi." << NOCOLOR << std::endl;
	std::cout << "\t- Aller dans le fichier " << YELLOW << "./class/Cmd_irssi/Cmd_irssi.cpp" << NOCOLOR
			  << " et modifier la méthode : " << MAGENTA << "Cmd_irssi::init_action(void)" << NOCOLOR << "." << std::endl;

	std::cout << "2. " << GREEN << "Pour interpréter la première commande :" << NOCOLOR << std::endl;
	std::cout << "\t- Modifier " << YELLOW << "./header/Constante.hpp" << NOCOLOR
			  << " pour ajouter une nouvelle action dans l'énumération " << RED << "ACTION" << NOCOLOR << "." << std::endl;
	std::cout << "\t- Respecter les commentaires et l'ordre, c'est très important !" << std::endl;

	std::cout << "3. " << CYAN << "Ajouter le message associé à cette nouvelle action dans le fichier :" << NOCOLOR << std::endl;
	std::cout << "\t- " << YELLOW << "./utils/define_array_and_get_element_of_array.cpp" << NOCOLOR << "." << std::endl;

	std::cout << "4. " << MAGENTA << "Pour finir :" << NOCOLOR << std::endl;
	std::cout << "\t- Créer la nouvelle méthode pour l'action dans " << YELLOW << "./class/Irssi_serv/Irssi_serv.hpp" << NOCOLOR << "." << std::endl;
	std::cout << "\t- Ne pas oublier de l'ajouter dans le constructeur dans " << YELLOW << "./class/Irssi_serv/Irssi_serv.cpp" << NOCOLOR << "." << std::endl;

	std::cout << std::endl;
	std::cout << RED << "/!\\ IMPORTANT : Respecter l'ordre et les commentaires pour éviter les erreurs." << NOCOLOR << std::endl;
	std::cout << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << WHITE << "-- BONNE CHANCE --" << GREEN << " (O_<)★彡" << NOCOLOR << std::endl;
}

int	main(int argc, char **argv)
{
	(void)	argc;
	(void)	argv;
	TO_DO();
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
		--track-fds=yes \
		--read-var-info=yes \
		./ircserv 8080 mdp

test a faire :

nc <ip> <port> <message>
	exemple :
	nc 127.0.0.1 8080 exit
*/