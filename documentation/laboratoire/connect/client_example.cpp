/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_example.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:15:06 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
	// Créer une socket
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	// Configurer l'adresse du serveur
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Adresse IP du serveur
	server_address.sin_port = htons(PORT); // Convertir le port en ordre d'octets réseau

	// Établir la connexion au serveur
	if (connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
		std::cerr << "Erreur de connexion au serveur" << std::endl;
		close(client_fd);
		return 1;
	}

	std::cout << "Connecté au serveur sur le port " << PORT << std::endl;

	// Envoyer un message au serveur
	const char* message = "Hello, Server!";
	send(client_fd, message, strlen(message), 0);
	std::cout << "Message envoyé: " << message << std::endl;

	// Recevoir une réponse du serveur
	char buffer[1024] = {0};
	ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
	if (bytes_received > 0) {
		std::cout << "Réponse du serveur: " << buffer << std::endl;
	}

	// Fermer la socket
	close(client_fd);
	return 0;
}
