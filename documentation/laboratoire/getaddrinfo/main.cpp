/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:37:31 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
	const char *hostname = "example.com"; // Nom de domaine du serveur
	const char *port = "80"; // Port du service

	// Structure pour stocker les résultats de getaddrinfo
	struct addrinfo hints;
	struct addrinfo *result, *rp;

	// Effacer la structure hints pour éviter des comportements imprévisibles
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    // Permet IPv4 ou IPv6
	hints.ai_socktype = SOCK_STREAM; // Utiliser une socket de type stream (TCP)
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          // Tout protocole

	// Obtenir la liste des adresses
	int s = getaddrinfo(hostname, port, &hints, &result);
	if (s != 0) {
		std::cerr << "Erreur dans getaddrinfo: " << gai_strerror(s) << std::endl;
		exit(EXIT_FAILURE);
	}

	// Boucle à travers toutes les adresses retournées et essayer de se connecter à une
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		int sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sockfd == -1)
			continue;

		if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1) {
			std::cout << "Connexion réussie à " << hostname << " sur le port " << port << std::endl;
			close(sockfd);
			break; // Succès
		}

		close(sockfd);
	}

	if (rp == NULL) {
		std::cerr << "Impossible de se connecter à " << hostname << " sur le port " << port << std::endl;
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result); // Libérer la liste des adresses

	return 0;
}
