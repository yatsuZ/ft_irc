/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:16:18 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:42:04 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::do_action(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << GREEN << "↓↓↓ -------- START OF INTERPRETION CMD ----------- ↓↓↓" << NOCOLOR << std::endl;
	std::cout << current_cmd << std::endl;
	Action act = current_cmd.get_action();
	current_user->get_msg_by_step(this->get_name(), current_pollfd);
	Reaction_Serv res = (this->*action_table[act])(current_cmd, current_user, current_pollfd, index_of_current_pollfd);
	std::cout << "↑↑↑ -------- END OF INTERPRETION CMD ----------- ↑↑↑" << std::endl;
	return (res);
}


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
					Reaction_Serv reaction = do_action(iter_cmd_irssi, _get_userhuman_by_index_of_pollfd(i), current_pollfd, i);
					if (reaction == PASS)
						break;
					else if (reaction == STOP)
						return;
				}
				list_cmd.clear();
				std::cout << std::endl;
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
	std::cout << BLUE << "V-✉-✉-✉-✉-✉-✉ Message recu ✉-✉-✉-✉-✉-✉-V" << NOCOLOR << std::endl;

	std::cout << RED << "\"" << NOCOLOR << buff.get_data_in_string() << RED << "\"" << NOCOLOR << std::endl;

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
		if (!(line[0] == CRLF[0] || line[0] == CRLF[1]))
			list_cmd.push_back(line);
	}
	return (list_cmd);
}