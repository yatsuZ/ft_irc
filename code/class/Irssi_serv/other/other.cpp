/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:14:20 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/24 23:25:36 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

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
	ssize_t index_pollfd = this->_all_pollfd.size() - 1;
	// std::cout << this->_all_pollfd << std::endl;
	Client new_client(this->_all_pollfd.size() - 1, client_addr, client_len);
	// std::cout << YELLOW << "New Client :\t" << NOCOLOR << new_client << std::endl;

	// cree un user par defaut
	UserHuman * exist = this->_get_userhuman_by_index_of_pollfd(index_pollfd);
	if (exist == NULL)
	{
		UserHuman new_user(new_client);
		this->_all_User.push_back(new_user);// cree un nouveaux user par defaut
		std::cout << this->_all_User << std::endl;
		std::cout << YELLOW << "New User :\t" << NOCOLOR << new_user << std::endl;

	}
}

bool	Irssi_serv::_nick_already_used(std::string nick) const
{
	for (size_t i = 0; i < this->_all_User.size(); i++)// Vérifier si le surnom est déjà utilisé par un autre utilisateur
	{
		if (this->_all_User[i].get_nick() == nick)
			return (true);
	}
	return (false);
}



