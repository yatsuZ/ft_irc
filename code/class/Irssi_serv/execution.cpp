/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:16:18 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 20:21:52 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Irssi_serv.hpp"


/// @brief Methode qui est le coeur du programme
void	Irssi_serv::exec(void)
{
	std::vector<Cmd_irssi>	list_cmd;
	pollfd	current_pollfd;
	std::cout << YELLOW << "Execution du Serveur ..." << NOCOLOR << std::endl;

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
					std::cout << iter_cmd_irssi << std::endl;
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
					// else if (iter_cmd_irssi.get_action() == IDK)
					// 	std::cout << iter_cmd_irssi << std::endl;
				}
				list_cmd.clear();
			}
		}
	}
}

/// @brief Quand pc transmet des info et communique et retorune une liste de commande irssi
std::vector<Cmd_irssi>	Irssi_serv::link(pollfd &current_pollfd)
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

	all_line = buff.get_data_in_vector_of_line();
	for (size_t i = 0; i < all_line.size(); ++i)
	{
		std::string line = all_line[i];
		if (is_sep(line[0], SEPERATOR_WITHOUT_SPACE_AND_TAB) == -1)
			list_cmd.push_back(line);
	}
	return (list_cmd);
}