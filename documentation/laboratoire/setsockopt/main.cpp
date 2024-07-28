/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:44:57 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	// Créer une socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	// Configurer l'option SO_REUSEADDR pour permettre la réutilisation de l'adresse
	int optval = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
		std::cerr << "Erreur dans setsockopt" << std::endl;
		close(sockfd);
		return 1;
	}

	std::cout << "Option SO_REUSEADDR définie avec succès" << std::endl;

	// Configurer l'adresse et le port du serveur
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); // Adresse IP du serveur
	server_address.sin_port = htons(8080); // Port du serveur

	// Associer la socket à l'adresse et au port spécifiés
	if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		std::cerr << "Erreur dans bind" << std::endl;
		close(sockfd);
		return 1;
	}

	std::cout << "Socket associée à l'adresse et au port" << std::endl;

	// Fermer la socket
	close(sockfd);
	return 0;
}