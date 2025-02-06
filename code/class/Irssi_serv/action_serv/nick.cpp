/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:23:39 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/06 16:31:16 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv Irssi_serv::ft_nick(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << PINK << "-------- NICK -----------" << NOCOLOR << std::endl;

	std::vector<std::string> list_dargument = current_cmd.get_arg();

	if (list_dargument.empty())
		return (send_message(ERR_NONICKNAMEGIVEN(this->get_name()), current_pollfd), (NONE));

	// Extraire le nickname du message
	std::string nick = list_dargument[0];  // Le premier argument de la commande NICK est le surnom

	// Vérifier que le surnom n'est pas vide et qu'il respecte les règles de longueur
	if (nick.empty() || nick.length() > 50)
		return (send_message(ERR_ERRONEUSNICKNAME(this->get_name(), nick), current_pollfd), (NONE));

	// Vérifier si le surnom est déjà utilisé par un autre utilisateur
	for (size_t i = 0; i < this->_all_User.size(); i++)
	{
		if (this->_all_User[i].getNick() == nick)
			return (send_message(ERR_NICKNAMEINUSE(this->get_name(), this->_all_User[i].getNick(), nick), current_pollfd), (NONE));
	}

	Client * current_client = this->_get_client_by_index_of_pollfd(index_of_current_pollfd);
	if (current_client == NULL)
			return (send_message(ERR_NOSUCHNICK(this->get_name(), nick), current_pollfd), (NONE));

	UserHuman new_user(nick, *current_client);
	_all_User.push_back(new_user);

	send_message(RPL_WELCOME(this->get_name(), new_user.getNick(), new_user.getName(), new_user.get_ip_to_string()), current_pollfd);
	send_message(RPL_YOURHOST(this->get_name(), new_user.getNick(), "<Yassine, Samira , Comme> 0.1"), current_pollfd);

	return (NONE);
}
