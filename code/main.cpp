/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:27:32 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/16 00:28:18 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/Ft_irc.hpp"

int	main(int argc, char **argv)
{
	(void)	argc;
	(void)	argv;

	std::cout << getColorCode(BLUE) << "Cree une classe serveur :" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t1. je dois utilise socket" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t2. Defenir de quoi j'ai besoin" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t3. Defenir quand es que jaurai reussi a cree un serveur" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t4. Lire les ecoutes" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t6. Revoir les fonction utiles" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t7. Prendre les parametres d'entrées | " << getColorCode(GREEN) << "FAIS" << getColorCode(NOCOLOR) << std::endl;
	std::cout << getColorCode(YELLOW) << "\t8. Faire des exception | " << getColorCode(GREEN) << "FAIS" << getColorCode(NOCOLOR) << std::endl;

	std::cout << std::endl;
	std::cout << getColorCode(RED) << "J'aurai reussi a cree un serveur Quand ...." << getColorCode(NOCOLOR) << std::endl;


	std::cout << "------------------" << std::endl;

	try
	{
		if (argc != 3 || !argv)
			throw Init_serv_error("Pas le bon nombre d'argument il en faut 2.");
		Server test(argv[1], argv[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << getColorCode(RED) << e.what() << getColorCode(NOCOLOR) << std::endl;
		return (1);
	}

	return (0);
}