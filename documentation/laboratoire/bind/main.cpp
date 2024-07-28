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
#include <arpa/inet.h>

#define PORT 8080

int main() {
	// Créer une socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	// Définir les options de socket (optionnel)
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cerr << "Erreur de setsockopt" << std::endl;
		close(server_fd);
		return 1;
	}

	// Configurer l'adresse du serveur
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // Utiliser n'importe quelle adresse locale disponible
	address.sin_port = htons(PORT); // Convertir le port en ordre d'octets réseau

	// Associer la socket à l'adresse et au port
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cerr << "Erreur de liaison de la socket (bind)" << std::endl;
		close(server_fd);
		return 1;
	}

	// Mettre la socket en écoute
	if (listen(server_fd, 3) < 0) {
		std::cerr << "Erreur de mise en écoute" << std::endl;
		close(server_fd);
		return 1;
	}

	std::cout << "Serveur en écoute sur le port " << PORT << std::endl;

	// Fermer la socket
	close(server_fd);
	return 0;
}
