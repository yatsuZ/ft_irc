/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:16:18 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/20 00:46:34 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

/// @brief Quand pc se connecte aux serveur
void	Server::connect(void)
{

	std::cout << "-------- CONNECTION -----------" << std::endl;
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	int client_fd = accept(this->get_socketfd(), (struct sockaddr*)&client_addr, &client_len);
	if (client_fd == -1)
	{
		perror("Accept failed");
		return;
	}

	// Ajouter le nouveau client à la liste
	pollfd client_pollfd = {client_fd, POLLIN | POLLOUT | POLLHUP, 0};
	this->_all_pollfd.push_back(client_pollfd);
	
// Verifier ici si il sagit dune reconexion ou un nvx compte heheh
	std::cout << this->_all_pollfd << std::endl;
}

/// @brief Quand pc transmet des info et communique
Action	Server::link(pollfd &current_pollfd)
{
	Action action = NO_ACTION;

	Data_buffer<char>	buff(current_pollfd.fd, &action);
	if (action != NO_ACTION)
		return (action);
	std::string message(buff.get_data_in_string());
	std::cout << "Message recu :" << message << std::endl;
	if (message == "exit\n")
		action = SHUTDOWN;
	return (action);
}

/// envoye un message aux client
void	Server::send_message(std::string message, pollfd &current_pollfd)
{
	std::cout << getColorCode(BLUE) << "Message envoyé aux pollfd" << getColorCode(NOCOLOR) << "(" << current_pollfd.fd << ") : \"" << getColorCode(GREEN) << message << getColorCode(NOCOLOR) << "\"";

	send(current_pollfd.fd, message.c_str(), message.size(), 0);
}


/// @brief Quand pc se deconnecte aux serveur
void	Server::disconnect(size_t i, pollfd &current_pollfd)
{
	std::cout << "-------- DECO -----------" << std::endl;

	this->_all_pollfd.erase(this->_all_pollfd.begin() + i);
	close(current_pollfd.fd);
	std::cout << this->_all_pollfd << std::endl;
}

/// @brief Methode qui est le coeur du programme
void	Server::exec(void)
{
	Action	action_a_faire = NO_ACTION;
	pollfd	current_pollfd;
	std::cout << getColorCode(YELLOW) << "Execution du Serveur ..." << getColorCode(NOCOLOR) << std::endl;

	// Boucle principale
	while (true)
	{
		// Poll pour attendre un événement
		int ret = poll(this->_all_pollfd.data(), this->_all_pollfd.size(), 5); // Attente pour des événements +  Utilise _all_pollfd.data() pour obtenir un pointeur sur le tableau interne
		if (ret < 0)
			this->_throw_except("Erreur de la fonction poll()");
		if (this->_all_pollfd[0].revents & POLLIN)
			this->connect();// Nouvelle connexion
		for (size_t i = 1; i < this->_all_pollfd.size(); i++)
		{
			current_pollfd = this->_all_pollfd[i];

			if (current_pollfd.revents & POLLIN)
				action_a_faire = this->link(current_pollfd);

			if (action_a_faire == SHUTDOWN)
				return ;
			else if (action_a_faire == DECO)
				this->disconnect(i--, current_pollfd);
			else if (action_a_faire == ERROR_RECV_DATA)
				this->send_message(std::string(getColorCode(RED)) + "Error de recv data Fail..." + std::string(getColorCode(NOCOLOR)), current_pollfd);
			action_a_faire = NO_ACTION;
		}
	}
}