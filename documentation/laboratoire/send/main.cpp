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

#define PORT 8080

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

	// Mettre la socket en écoute des connexions entrantes
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

	// Message HTTP à envoyer au client
	const char* http_response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 46\r\n"
		"\r\n"
		"<html><body><h1>Bonjour, client !</h1> </body></html>";

	// Utiliser la fonction send pour envoyer des données au client
	ssize_t bytes_sent = send(client_fd, http_response, strlen(http_response), 0);
	if (bytes_sent < 0) {
		std::cerr << RED << "Erreur d'envoi du message" << NOCOLOR << std::endl;
	} else {
		std::cout << GREEN << "Message envoyé au client" << NOCOLOR << std::endl;
	}

	// Fermer la socket client
	close(client_fd);
	std::cout << GREEN << "Connexion fermée" << NOCOLOR << std::endl;

	// Fermer la socket serveur
	close(server_fd);
	std::cout << GREEN << "Socket serveur fermée" << NOCOLOR << std::endl;

	return 0;
}
