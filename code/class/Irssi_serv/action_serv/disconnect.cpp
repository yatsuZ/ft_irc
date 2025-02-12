/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:22:31 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/10 23:15:49 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

void	Irssi_serv::_errase_client_from_tab(pollfd &current_pollfd)
{
	std::cout << "All_client :" << std::endl;

	bool find_client_associate_by_pollfd = false;
	for (std::vector<Client>::iterator iteration_client = this->_all_Client.begin();
	iteration_client != this->_all_Client.end(); iteration_client++)
	{
		ssize_t index_pollfd = iteration_client->get_index_pollfd();
		if (index_pollfd != -1 && current_pollfd.fd == this->_all_pollfd[index_pollfd].fd)
		{
			std::cout << RED << "Client to erase :\t" << NOCOLOR << *iteration_client << std::endl;
			iteration_client = this->_all_Client.erase(iteration_client);
			if (iteration_client == this->_all_Client.end())
				break ;
			find_client_associate_by_pollfd = true;
		}
		if (find_client_associate_by_pollfd)
			iteration_client->set_index_pollfd(iteration_client->get_index_pollfd() - 1);
		std::cout << "\t- " << *iteration_client << std::endl;
	}
}

void	Irssi_serv::_errase_user_from_tab(pollfd &current_pollfd)
{
	std::cout << "All_User :" << std::endl;

	bool find_user_associate_by_pollfd = false;
	for (std::vector<UserHuman>::iterator iteration_user = this->_all_User.begin();
	iteration_user != this->_all_User.end(); iteration_user++)
	{
		ssize_t index_pollfd = iteration_user->get_index_pollfd();
		if (index_pollfd != -1 && current_pollfd.fd == this->_all_pollfd[index_pollfd].fd)
		{
			std::cout << RED << "User to erase :\t" << NOCOLOR << *iteration_user << std::endl;
			iteration_user = this->_all_User.erase(iteration_user);
			if (iteration_user == this->_all_User.end())
				break ;
			find_user_associate_by_pollfd = true;
		}
		if (find_user_associate_by_pollfd)
			iteration_user->set_index_pollfd(iteration_user->get_index_pollfd() - 1);
		std::cout << "\t- " << *iteration_user << std::endl;
	}
}


/// @brief Quand pc se deconnecte aux serveur
Reaction_Serv	Irssi_serv::ft_disconnect(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	std::cout << RED << "◐◐◐◐◐◐◐◐◐◐◐ DISCONNECT ◑◑◑◑◑◑◑◑◑◑◑" << NOCOLOR << std::endl;// surpimer le client
	
	this->_all_pollfd.erase(this->_all_pollfd.begin() + index_of_current_pollfd);
	close(current_pollfd.fd);
	std::cout << this->_all_pollfd << std::endl;

	this->_errase_client_from_tab(current_pollfd);
	this->_errase_user_from_tab(current_pollfd);
	index_of_current_pollfd--;
	return (PASS);
}
