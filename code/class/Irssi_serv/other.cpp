/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:14:20 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/09 17:13:12 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Irssi_serv.hpp"

/// @brief Quand pc se connecte aux serveur
void	Irssi_serv::connect(void)
{
	std::cout << GREEN << "◑◑◑◑◑◑◑◑◑◑◑ CONNECTION ◐◐◐◐◐◐◐◐◐◐◐" << NOCOLOR << std::endl;
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

	// cree un user par defaut
	Client * last_client = _get_client_by_index_of_pollfd(this->_all_pollfd.size() - 1);
	std::cout << YELLOW << "last_client  :\t" << NOCOLOR << *last_client << std::endl;
	ssize_t index = last_client->get_index_pollfd();
	std::cout << YELLOW << "last_client->get_index_pollfd()  :\t" << NOCOLOR << index << std::endl;

	UserHuman * exist = this->_get_userhuman_by_index_of_pollfd(index);
	if (exist == NULL)
	{
		UserHuman new_user(*last_client);
		this->_all_User.push_back(new_user);// cree un nouveaux user par defaut
	}
}

/// envoye un message aux client
int	Irssi_serv::send_message(std::string message, pollfd &current_pollfd)
{
	std::cout << BLUE << "Message envoyé aux pollfd" << NOCOLOR << "(" << current_pollfd.fd << ") : " << GREEN << "\"" << NOCOLOR << message << GREEN << "\"" << NOCOLOR << std::endl;

	send(current_pollfd.fd, message.c_str(), message.size(), 0);
	return (0);
}

Client * Irssi_serv::_get_client_by_index_of_pollfd(ssize_t i)
{
	if (i == -1)
		return (NULL);
	for (size_t j = 0; j < this->_all_Client.size(); j++)
	{
		if (this->_all_Client[j].get_index_pollfd() == i)
			return (&(this->_all_Client[j]));
	}
	return (NULL);
}

UserHuman * Irssi_serv::_get_userhuman_by_index_of_pollfd(ssize_t i)
{
	if (i == -1)
		return (NULL);
	for (size_t j = 0; j < this->_all_User.size(); j++)
	{
		if (this->_all_User[j].get_index_pollfd() == i)
			return (&(this->_all_User[j]));
	}
	return (NULL);
}

bool	Irssi_serv::_nick_already_used(std::string nick) const
{
	for (size_t i = 0; i < this->_all_User.size(); i++)// Vérifier si le surnom est déjà utilisé par un autre utilisateur
	{
		if (this->_all_User[i].getNick() == nick)
			return (true);
	}
	return (false);
}
