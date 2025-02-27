/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:14:20 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/27 16:18:46 by yzaoui           ###   ########.fr       */
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

// int	send_message(std::string message, pollfd &current_pollfd)

/// @brief envoye un msg a tout un chanelle sauf a celui qui envoye le msg
/// @param emeteur celui qui envoye le msg
/// @param chan le chanelle dans le quelle cest dis
/// @param msg le message envoyer
void	Irssi_serv::_send_message_to_a_chanelle(UserHuman &emeteur, Channel &chan, const std::string msg)
{
	ssize_t emeteur_index_fd = emeteur.get_index_pollfd();
	std::vector<size_t> all_user_from_this_chan = chan.get_index_users();
	for (std::vector<size_t>::iterator i = all_user_from_this_chan.begin(); i != all_user_from_this_chan.end(); i++)
	{
		ssize_t current_index_fd = this->_all_User[*i].get_index_pollfd();
		if (current_index_fd > -1 && current_index_fd != emeteur_index_fd)
			send_message(msg, this->_all_pollfd[current_index_fd]);
	}
	
}

/// @brief envoye un msg a tout les chanelles d'un user
/// @param emeteur celui qui envoye le msg
/// @param msg le message envoyer
void	Irssi_serv::_send_message_to_a_all_chanelle(UserHuman &emeteur, const std::string msg)
{
	std::vector<size_t> all_chan_from_this_user = emeteur.get_chans();
	for (std::vector<size_t>::iterator i = all_chan_from_this_user.begin(); i != all_chan_from_this_user.end(); i++)
	{
		this->_send_message_to_a_chanelle(emeteur, this->_all_Channel[*i], msg);
	}
	
}

