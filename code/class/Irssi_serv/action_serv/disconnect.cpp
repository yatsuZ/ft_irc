/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:22:31 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:43:32 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"


void	Irssi_serv::_errase_user_from_tab(pollfd &current_pollfd)
{
	std::cout << "All_Client :" << std::endl;

	bool find_user_associate_by_pollfd = false;
	for (std::vector<UserHuman>::iterator iteration_user = this->_all_User.begin();
	iteration_user != this->_all_User.end(); iteration_user++)
	{
		ssize_t index_pollfd = iteration_user->get_index_pollfd();
		if (index_pollfd != -1 && current_pollfd.fd == this->_all_pollfd[index_pollfd].fd)
		{
			std::cout << RED << "Client to erase :\t" << NOCOLOR << static_cast<Client>(*iteration_user) << std::endl;//modifier laffichage
			iteration_user = this->_all_User.erase(iteration_user);
			if (iteration_user == this->_all_User.end())
				break ;
			find_user_associate_by_pollfd = true;
		}
		if (find_user_associate_by_pollfd)
			iteration_user->set_index_pollfd(iteration_user->get_index_pollfd() - 1);
		std::cout << "\t- " << static_cast<Client>(*iteration_user) << std::endl;
	}
}


/// @brief Quand pc se deconnecte aux serveur
Reaction_Serv	Irssi_serv::ft_disconnect(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;
	(void)	current_cmd;
	std::cout << RED << "◐◐◐◐◐◐◐◐◐◐◐ DISCONNECT ◑◑◑◑◑◑◑◑◑◑◑" << NOCOLOR << std::endl;// surpimer le client
	
	this->_all_pollfd.erase(this->_all_pollfd.begin() + index_of_current_pollfd);
	close(current_pollfd.fd);
	std::cout << this->_all_pollfd << std::endl;

	this->_errase_user_from_tab(current_pollfd);
	index_of_current_pollfd--;
	return (PASS);
}
