/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/18 15:03:53 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
	// Créer la socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	// Configurer l'adresse du serveur
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Lier la socket à l'adresse
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cerr << "Erreur de liaison de la socket" << std::endl;
		close(server_fd);
		return 1;
	}

	// Écouter les connexions entrantes
	if (listen(server_fd, 1) < 0) {
		std::cerr << "Erreur de mise en écoute" << std::endl;
		close(server_fd);
		return 1;
	}

	std::cout << "Serveur en écoute sur le port " << PORT << std::endl;
	std::cout << "http://localhost:" << PORT << "/" << std::endl;
	// Accepter une connexion entrante
	int client_fd = accept(server_fd, NULL, NULL);
	if (client_fd < 0) {
		std::cerr << "Erreur d'acceptation de la connexion" << std::endl;
		close(server_fd);
		return 1;
	}

	// Lire les données envoyées par le client
	char buffer[BUFFER_SIZE] = {0};
	ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0) {
		std::cerr << "Erreur de lecture des données" << std::endl;
		close(client_fd);
		close(server_fd);
		return 1;
	}

	std::cout << "Message reçu: " << buffer << std::endl;

	// Répondre au client
	const char* response = "Message reçu";
	send(client_fd, response, strlen(response), 0);

	// Fermer les sockets
	close(client_fd);
	close(server_fd);

	return 0;
}
