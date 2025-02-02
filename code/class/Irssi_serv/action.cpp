/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:00 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/31 01:45:45 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_no_action(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << "-------- NO ACTION -----------" << std::endl;

	return (NONE);
}

Reaction_Serv	Irssi_serv::ft_error_recv_data(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	index_of_current_pollfd;
	std::cout << "-------- ERROR OF FUNCTION RECV -----------" << std::endl;

	this->send_message(std::string(getColorCode(RED)) + "Error de recv data Fail..." + std::string(getColorCode(NOCOLOR)), current_pollfd);
	return (NONE);
}

Reaction_Serv	Irssi_serv::ft_shutdown(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << "-------- SHUTDOWN -----------" << std::endl;

	return (STOP);
}

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

Reaction_Serv	Irssi_serv::ft_cap(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << PINK << "-------- CAPACITI -----------" << NOCOLOR << std::endl;

	return (NONE);
}

Reaction_Serv Irssi_serv::ft_nick(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << PINK << "-------- NICK -----------" << NOCOLOR << std::endl;

	return (NONE);
}

Reaction_Serv	Irssi_serv::ft_user(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;

	std::cout << PINK << "-------- USER -----------" << NOCOLOR << std::endl;

	return (NONE);
}

Reaction_Serv	Irssi_serv::ft_idk(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << YELLOW << "-------- I DONT KNOW ?? -----------" << NOCOLOR << std::endl;

	// std::cout << current_cmd << std::endl;
	return (NONE);
}
