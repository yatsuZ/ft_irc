/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:58:16 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fcntl.h>    // Pour fcntl
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

	// Obtenir les flags actuels de la socket
	int flags = fcntl(sockfd, F_GETFL, 0);
	if (flags < 0) {
		std::cerr << "Erreur dans fcntl (F_GETFL)" << std::endl;
		close(sockfd);
		return 1;
	}

	// Définir la socket en mode non-bloquant
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
		std::cerr << "Erreur dans fcntl (F_SETFL)" << std::endl;
		close(sockfd);
		return 1;
	}

	std::cout << "Socket définie en mode non-bloquant" << std::endl;

	// Fermer la socket
	close(sockfd);
	return 0;
}