/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/28 14:01:28 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>

// Définir les couleurs
#define NOCOLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define PURPLE "\033[35m"

int main() {
	// Adresse IP en format texte
	const char* ip_address = "192.168.1.1";

	std::cout << CYAN << "Conversion de l'adresse IP: " << ip_address << NOCOLOR << std::endl;

	// Utilisation de inet_addr
	in_addr_t addr = inet_addr(ip_address);

	// Vérification si inet_addr a réussi
	if (addr == INADDR_NONE) {
		std::cerr << RED << "Erreur: Adresse IP invalide." << NOCOLOR << std::endl;
		return 1;
	}

	// Affichage de l'adresse IP convertie
	std::cout << GREEN << "Adresse IP convertie en format binaire: " << addr << NOCOLOR << std::endl;

	// Affichage de l'adresse IP convertie en format lisible
	struct in_addr ip_addr;
	ip_addr.s_addr = addr;
	std::cout << YELLOW << "Adresse IP reconvertie en format texte: " << inet_ntoa(ip_addr) << NOCOLOR << std::endl;

	return 0;
}
