/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/28 14:13:42 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>

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
	// Adresse IP en format binaire
	in_addr_t binary_ip = inet_addr("192.168.1.1");

	if (binary_ip == INADDR_NONE) {
		std::cerr << RED << "Erreur: Adresse IP invalide." << NOCOLOR << std::endl;
		return 1;
	}

	struct in_addr ip_addr;
	ip_addr.s_addr = binary_ip;

	// Utilisation de inet_ntoa
	const char* ip_str = inet_ntoa(ip_addr);

	if (ip_str == NULL) {
		std::cerr << RED << "Erreur: Conversion de l'adresse IP échouée." << NOCOLOR << std::endl;
		return 1;
	}

	std::cout << GREEN << "Adresse IP en format texte: " << ip_str << NOCOLOR << std::endl;

	return 0;
}
