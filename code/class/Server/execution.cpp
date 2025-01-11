/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:16:18 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/11 01:26:14 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

/// @brief Quand pc se connecte aux serveur
void	Server::connect(void)
{
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int client_fd = accept(this->get_socketfd(), (struct sockaddr*)&client_addr, &client_len);
	if (client_fd == -1)
	{
		perror("Accept failed");
		return;
	}

	// Ajouter le nouveau client à la liste
	pollfd client_pollfd = {client_fd, POLLIN, 0};
	this->_fds.push_back(client_pollfd);

	std::cout << "Client connecté : FD = " << client_fd << std::endl;
}

/// @brief Quand pc transmet des info et communique
void	Server::link(int client_fd)
{
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));

	ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received <= 0)
	{
		perror("Reception failed");
		return;
	}

	std::cout << "Message reçu de FD " << client_fd << ": " << buffer << std::endl;

	// Echo du message à tous les autres clients
	for (std::vector<pollfd>::iterator client = this->_fds.begin(); client != this->_fds.end(); client++)
	{
		if ((*client).fd != this->_fds[0].fd && (*client).fd != client_fd)
			send((*client).fd, buffer, bytes_received, 0);
	}
}

/// @brief Quand pc se deconnecte aux serveur
void	Server::disconnect(int client_index)
{
	std::cout << "Client déconnecté : FD = " << this->_fds[client_index].fd << std::endl;
	close(this->_fds[client_index].fd);
	this->_fds.erase(this->_fds.begin() + client_index);

}

/// @brief Methode qui est le coeur du programme
void	Server::exec(void)
{
	std::cout << getColorCode(YELLOW) << "Execution du Serveur ..." << getColorCode(NOCOLOR) << std::endl;

	// Boucle principale
	while (true)
	{
		// Poll pour attendre un événement
		int ret = poll(this->_fds.data(), this->_fds.size(), 5); // Attente infinie pour des événements +  Utilise _fds.data() pour obtenir un pointeur sur le tableau interne
		if (ret < 0)
			this->_throw_except("Erreur de la fonction poll()");

		for (size_t i = 0; i < this->_fds.size(); ++i)
		{
			if (this->_fds[i].revents & POLLIN)
			{
				if (!i)
					this->connect();// Nouvelle connexion
				else
				{
					// Données reçues ou déconnexion
					char buffer[1];
					ssize_t check = recv(this->_fds[i].fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT);
					if (check == 0)
					{
						this->disconnect(i);
						--i; // Réajuster l'index après suppression
					}
					else
						this->link(this->_fds[i].fd);
				}
			}
		}
	}
}


/// @brief Methode qui est le coeur du programme Ancienne version
void	Server::old_exec(void)
{
	std::cout << getColorCode(YELLOW) << "Execution du Serveur ..." << getColorCode(NOCOLOR) << std::endl;

	// Boucle principale
	while (true)
	{
		// Poll pour attendre un événement
		int ret = poll(this->_fds.data(), this->_fds.size(), 5); // Attente infinie pour des événements +  Utilise _fds.data() pour obtenir un pointeur sur le tableau interne
		if (ret < 0)
			this->_throw_except("Erreur de la fonction poll()");

		// Vérification si la socket serveur est prête à accepter une connexion
		if (this->_fds[0].revents & POLLIN)
		{
			sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			int client_fd = accept(_socketfd, (struct sockaddr*)&client_addr, &client_len);
			if (client_fd < 0)
			{
				std::cerr << getColorCode(RED) << "Erreur d'acceptation de la connexion" << getColorCode(NOCOLOR) << std::endl;
				break;
			}
			std::cout << getColorCode(GREEN) << "Connexion acceptée!" << getColorCode(NOCOLOR) << std::endl;

			// Lire les données envoyées par le client
			char buffer[BUFFER_SIZE] = {0};
			ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				std::cerr << getColorCode(RED) << "Erreur de lecture des données" << getColorCode(NOCOLOR) << std::endl;
				close(client_fd);
				break;
			}
			// std::cout << "BUFFER = \"" << buffer << "\"" << std::endl;
			if (std::string(buffer) == "exit\n")
			{
				close(client_fd);
				break;
			}
			std::cout << getColorCode(CYAN) << "Message reçu: " << getColorCode(NOCOLOR) << getColorCode(MAGENTA) << buffer << getColorCode(NOCOLOR) << std::endl;

			// Répondre au client
			const char* response = "Message reçu";
			send(client_fd, response, strlen(response), 0);
			std::cout << getColorCode(GREEN) << "Réponse envoyée au client" << getColorCode(NOCOLOR) << std::endl;

			// Fermer la connexion avec le client
			close(client_fd);
		}
	}
	std::cout << getColorCode(YELLOW) << "FIN DU SERVEUR" << getColorCode(NOCOLOR) << std::endl;
}
