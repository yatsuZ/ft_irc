/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:23:39 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/06 09:49:42 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv Irssi_serv::ft_nick(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
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
		if (this->_all_User[i].getNick() == nick) {
			// Envoie un message d'erreur si le surnom est déjà pris
			send_message(":server 433 " + nick + " :Nickname is already in use", current_pollfd);  // ERR_NICKNAMEINUSE
			return (NONE);  // Aucun changement dans l'état du serveur
		}
	}

	// S'il n'y a pas d'utilisateur avec ce surnom, l'utilisateur peut l'adopter
	// Associer le surnom au client
	Client * current_client = this->_get_client_by_index_of_pollfd(index_of_current_pollfd);
	if (current_client == NULL)
	{
			send_message(":server ??? " + nick + " : dont find this client", current_pollfd);
			return (NONE);
	}
	UserHuman new_user(nick, *current_client);
	_all_User.push_back(new_user);

	// Envoyer un message de bienvenue au client
	send_message("001 " + nick + " :Welcome to the Internet Relay Network " + nick + "\r\n", current_pollfd);  // RPL_WELCOME
	send_message("002 " + nick + " :Your host is irc.server.com, running version 1.0"+ "\r\n", current_pollfd);  // RPL_YOURHOST

	return (NONE);
}
