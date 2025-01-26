/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:00 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 20:13:24 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Irssi_serv.hpp"

/// @brief Quand pc se connecte aux serveur
void	Irssi_serv::connect(void)
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

/// @brief Quand pc se deconnecte aux serveur
void	Irssi_serv::disconnect(size_t i, pollfd &current_pollfd)
{
	std::cout << "-------- DECO -----------" << std::endl;

	this->_all_pollfd.erase(this->_all_pollfd.begin() + i);
	close(current_pollfd.fd);
	std::cout << this->_all_pollfd << std::endl;
}

/// envoye un message aux client
void	Irssi_serv::send_message(std::string message, pollfd &current_pollfd)
{
	std::cout << BLUE << "Message envoyé aux pollfd" << NOCOLOR << "(" << current_pollfd.fd << ") : \"" << GREEN << message << NOCOLOR << "\"";

	send(current_pollfd.fd, message.c_str(), message.size(), 0);
}