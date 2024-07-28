/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_example.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:14:26 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:14:38 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
	int server_fd, new_socket;
	sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	// Créer une socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	// Attacher la socket au port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "Erreur de setsockopt" << std::endl;
		close(server_fd);
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Associer la socket à l'adresse et au port
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		std::cerr << "Erreur de bind" << std::endl;
		close(server_fd);
		return 1;
	}

	// Mettre la socket en écoute
	if (listen(server_fd, 3) < 0) {
		std::cerr << "Erreur de listen" << std::endl;
		close(server_fd);
		return 1;
	}

	std::cout << "Serveur en écoute sur le port " << PORT << std::endl;

	// Accepter une connexion entrante
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		std::cerr << "Erreur de accept" << std::endl;
		close(server_fd);
		return 1;
	}

	// Lire le message du client
	char buffer[1024] = {0};
	read(new_socket, buffer, 1024);
	std::cout << "Message reçu du client: " << buffer << std::endl;

	// Envoyer une réponse au client
	const char* response = "Hello, Client!";
	send(new_socket, response, strlen(response), 0);
	std::cout << "Réponse envoyée au client" << std::endl;

	// Fermer la socket
	close(new_socket);
	close(server_fd);
	return 0;
}
