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

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
	// Créer la socket serveur
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		std::cerr << RED << "Erreur de création de la socket" << NOCOLOR << std::endl;
		return 1;
	}
	std::cout << GREEN << "Socket créée avec succès" << NOCOLOR << std::endl;

	// Configurer l'adresse du serveur
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Lier la socket à l'adresse et au port
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cerr << RED << "Erreur de liaison de la socket" << NOCOLOR << std::endl;
		close(server_fd);
		return 1;
	}
	std::cout << GREEN << "Socket liée avec succès" << NOCOLOR << std::endl;

	// Écouter les connexions entrantes
	if (listen(server_fd, 1) < 0) {
		std::cerr << RED << "Erreur de mise en écoute" << NOCOLOR << std::endl;
		close(server_fd);
		return 1;
	}
	std::cout << GREEN << "Serveur en écoute sur le port " << PORT << NOCOLOR << std::endl;

	// Accepter une connexion entrante
	sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);
	int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len);
	if (client_fd < 0) {
		std::cerr << RED << "Erreur d'acceptation de la connexion" << NOCOLOR << std::endl;
		close(server_fd);
		return 1;
	}
	std::cout << GREEN << "Connexion acceptée" << NOCOLOR << std::endl;

	// Lire les données envoyées par le client
	char buffer[BUFFER_SIZE] = {0};
	ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0) {
		std::cerr << RED << "Erreur de lecture des données" << NOCOLOR << std::endl;
		close(client_fd);
		close(server_fd);
		return 1;
	}
	std::cout << CYAN << "Message reçu: " << NOCOLOR << PURPLE << buffer << NOCOLOR << std::endl;

	// Répondre au client
	const char* response = "Message reçu";
	send(client_fd, response, strlen(response), 0);
	std::cout << GREEN << "Réponse envoyée au client" << NOCOLOR << std::endl;

	// Fermer les sockets
	close(client_fd);
	close(server_fd);
	std::cout << GREEN << "Sockets fermées" << NOCOLOR << std::endl;

	return 0;
}
