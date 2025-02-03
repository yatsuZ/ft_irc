/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:22:31 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/03 13:24:23 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/// @brief Quand pc se deconnecte aux serveur
Reaction_Serv	Irssi_serv::ft_disconnect(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	std::cout << "-------- DISCONNECT -----------" << std::endl;// surpimer le client
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
	
	this->_all_pollfd.erase(this->_all_pollfd.begin() + index_of_current_pollfd);
	close(current_pollfd.fd);
	std::cout << this->_all_pollfd << std::endl;
	index_of_current_pollfd--;
	return (PASS);
}
