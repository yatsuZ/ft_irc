/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:51:50 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ostream>
#include <iostream>

#define PORT 8080

int main() {
	// Créer une socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	// Configurer l'adresse et le port du serveur
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); // Adresse IP du serveur
	server_address.sin_port = htons(PORT); // Port du serveur

	// Associer la socket à l'adresse et au port spécifiés
	if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		std::cerr << "Erreur dans bind" << std::endl;
		close(sockfd);
		return 1;
	}

	// Obtenir l'adresse locale associée à la socket
	struct sockaddr_in local_address;
	socklen_t addr_len = sizeof(local_address);
	if (getsockname(sockfd, (struct sockaddr*)&local_address, &addr_len) < 0) {
		std::cerr << "Erreur dans getsockname" << std::endl;
		close(sockfd);
		return 1;
	}

	std::cout << "Adresse locale : " << inet_ntoa(local_address.sin_addr) << std::endl;
	std::cout << "Port local : " << ntohs(local_address.sin_port) << std::endl;

	// Fermer la socket
	close(sockfd);
	return 0;
}
