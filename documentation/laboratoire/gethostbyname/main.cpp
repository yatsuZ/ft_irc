/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/28 13:30:36 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
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
	// Nom d'hôte à résoudre
	const char* hostname = "www.example.com";

	std::cout << CYAN << "Résolution de l'adresse IP pour le nom d'hôte: " << hostname << NOCOLOR << std::endl;

	// Utilisation de gethostbyname
	struct hostent* host_info = gethostbyname(hostname);

	// Vérification si gethostbyname a réussi
	if (host_info == NULL) {
		std::cerr << RED << "Erreur: Échec de la résolution du nom d'hôte." << NOCOLOR << std::endl;
		return 1;
	}

	// Affichage des informations
	std::cout << GREEN << "Nom officiel: " << host_info->h_name << NOCOLOR << std::endl;

	// Liste des alias
	std::cout << YELLOW << "Alias: " << NOCOLOR;
	for (char** alias = host_info->h_aliases; *alias != NULL; ++alias) {
		std::cout << *alias << " ";
	}
	std::cout << std::endl;

	// Adresse IP
	std::cout << BLUE << "Adresses IP: " << NOCOLOR;
	for (char** addr = host_info->h_addr_list; *addr != NULL; ++addr) {
		struct in_addr ip_addr;
		std::memcpy(&ip_addr, *addr, sizeof(struct in_addr));
		std::cout << inet_ntoa(ip_addr) << " ";
	}
	std::cout << std::endl;

	return 0;
}
