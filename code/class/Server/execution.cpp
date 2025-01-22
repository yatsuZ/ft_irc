/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:16:18 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/23 00:01:11 by yzaoui           ###   ########.fr       */
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

/// @brief Quand pc transmet des info et communique et retorune une liste de commande irssi
std::vector<Cmd_irssi>	Server::link(pollfd &current_pollfd)
{
	std::vector<Cmd_irssi>		list_cmd;
	std::vector<std::string>	all_line;
	Action action = NO_ACTION;

	Data_buffer<char>	buff(current_pollfd.fd, &action);

	if (action != NO_ACTION)
	{
		Cmd_irssi n(action);
		list_cmd.push_back(n);
		return (list_cmd);
	}

	std::string message(buff.get_data_in_string());

//	std::cout << "Message recu :" << message << std::endl;

	all_line = ft_split(message, "\n\r");
	for (size_t i = 0; i < all_line.size(); ++i)
	{
		std::string line = all_line[i]; /// ICI sa dconne a refaire
		Cmd_irssi cmd(line);
		// std::cout << cmd << std::endl;
		list_cmd.push_back(cmd);
	}
	return (list_cmd);
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
	std::vector<Cmd_irssi>	list_cmd;
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
			{
				list_cmd = this->link(current_pollfd);

				for (size_t index_cmd = 0; index_cmd < list_cmd.size(); ++index_cmd)
				{
					Cmd_irssi iter_cmd_irssi(list_cmd[index_cmd]);
					std::cout << "index_cmd = " << index_cmd << " | " << iter_cmd_irssi << std::endl;
					if (iter_cmd_irssi.get_action() == SHUTDOWN)
						return ;
					else if (iter_cmd_irssi.get_action() == DECO)
					{
						this->disconnect(i, current_pollfd);
						i--;
						break;
					}
					else if (iter_cmd_irssi.get_action() == ERROR_RECV_DATA)
						this->send_message(std::string(getColorCode(RED)) + "Error de recv data Fail..." + std::string(getColorCode(NOCOLOR)), current_pollfd);
					else if (iter_cmd_irssi.get_action() == IDK)
						std::cout << iter_cmd_irssi << std::endl;

				}
			}
		}
	}
}