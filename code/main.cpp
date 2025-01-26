/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:27:32 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 23:19:06 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./affichage.ipp"

void TO_DO(void)
{
	std::cout << BLUE << "SALUT voici ce qu'il a faire." << NOCOLOR << std::endl;
	std::cout <<"Faire linterpretation des action recu du client irssi pour cela."  << std::endl;
	std::cout <<"aller dans le fichier" << YELLOW << "./class/Cmd_irssi/Cmd_irssi.cpp" << NOCOLOR << " dans cette methode : " << MAGENTA << "Cmd_irssi::init_action(void)" << NOCOLOR << std::endl;
	std::cout << GREEN << "Pour interpreter la premiere commande" << NOCOLOR << std::endl;
	std::cout << "Il faudra aussi aller dans " << YELLOW << "./header/Constante.hpp" << NOCOLOR << " pour ajouter dans lenum " << RED << "ACTION" << NOCOLOR
	<< " le nouveaux ACTION enum il faudra aussi aller dans " << YELLOW << "./header/Constante.hpp" << NOCOLOR << std::endl;
	std::cout << "Et" << std::endl;
	std::cout << YELLOW << "./utils/define_array_and_get_element_of_array.cpp" << NOCOLOR << " pour ajouter le message de cette nouvelle action ce quelle fais ou etc." << std::endl;
	std::cout << RED << "/!\\ RESPECTER LES COMMENTAIRES LE MEME ORDRE TRES IMPORTANT. " << NOCOLOR << std::endl;
	
	std::cout << "Pour finir aller dans Irssi_serv.hpp pour crée la nouvelle methode de laction. Ne pas oublier de rajouter dans le constructeur et hope FINI." <<std::endl;
	std::cout << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "--BONNE-CHANCE--" << GREEN << ";D" << NOCOLOR << std::endl;

}

int	main(int argc, char **argv)
{
	(void)	argc;
	(void)	argv;
	TO_DO();
	std::cout << "------------------" << std::endl;
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