/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:14:20 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/31 01:01:45 by yzaoui           ###   ########.fr       */
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
	std::cout << this->_all_pollfd << std::endl;
	Client new_client(this->_all_pollfd.size() - 1, client_addr, client_len);
	std::cout << YELLOW << "New Client :\t" << NOCOLOR << new_client << std::endl;
	this->_all_Client.push_back(new_client);
}

/// envoye un message aux client
int	Irssi_serv::send_message(std::string message, pollfd &current_pollfd)
{
	std::cout << BLUE << "Message envoyé aux pollfd" << NOCOLOR << "(" << current_pollfd.fd << ") : \"" << GREEN << message << NOCOLOR << "\"";

	send(current_pollfd.fd, message.c_str(), message.size(), 0);
	return (0);
}