/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 01:01:47 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>   // Pour close
#include <sys/socket.h> // Pour socket
#include <netinet/in.h> // Pour sockaddr_in
#include <cstring>    // Pour memset

#define PORT 8080

int main() {
	// Créer une socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	std::cout << "Socket créée avec succès" << std::endl;

	// Configurer l'adresse du serveur
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY; // Adresse IP du serveur
	server_address.sin_port = htons(PORT); // Convertir le port en ordre d'octets réseau

	// Lier la socket à l'adresse
	if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		std::cerr << "Erreur de liaison de la socket" << std::endl;
		close(sockfd);
		return 1;
	}

	std::cout << "Socket liée à l'adresse " << PORT << std::endl;

	// Fermer la socket
	if (close(sockfd) < 0) {
		std::cerr << "Erreur lors de la fermeture de la socket" << std::endl;
		return 1;
	}

	std::cout << "Socket fermée avec succès" << std::endl;

	return 0;
}