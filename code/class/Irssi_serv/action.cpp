/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:00 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/03 13:18:16 by yzaoui           ###   ########.fr       */
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

//commande otpionelle
Reaction_Serv	Irssi_serv::ft_cap(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << PINK << "-------- CAPACITI -----------" << NOCOLOR << std::endl;

	std::string msg;

	msg += ":serveur ";
	msg += current_cmd.get_cmd();// ou // msg += Fonctionalite_du_serveur_tab[CAP];
	msg += " * ";
	std::vector<std::string> list_dargument = current_cmd.get_arg();
	if (list_dargument.size() == 1 && list_dargument[0] == "LS")
	{
		msg += "LS :";
		// for (size_t i = 0; i < size_t(NBR_DE_FONCTIONALITE_DU_SERV); i++)
		// {
		// 	if (i != 0)
		// 		msg += " ";
		// 	msg += Fonctionalite_du_serveur_tab[i];
		// }
		msg += "\r\n";
		this->send_message(msg, current_pollfd);
	}

	return (NONE);
}

Reaction_Serv Irssi_serv::ft_nick(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << PINK << "-------- NICK -----------" << NOCOLOR << std::endl;

	std::vector<std::string> list_dargument = current_cmd.get_arg();
	// Vérifier si un argument (le surnom) a été fourni
	if (list_dargument.empty()) {
		// Si aucun argument n'est donné, envoyer l'erreur 431 : "No nickname given"
		send_message(":server 431 * :No nickname given", current_pollfd);
		return (NONE);
	}

	// Extraire le nickname du message
	std::string nick = list_dargument[0];  // Le premier argument de la commande NICK est le surnom

	// Vérifier que le surnom n'est pas vide et qu'il respecte les règles de longueur
	if (nick.empty() || nick.length() > 50) {
		// Envoie un message d'erreur pour un surnom invalide
		send_message(":server 432 * :Erroneous nickname", current_pollfd);  // ERR_ERRONEUSNICKNAME
		return (NONE);  // Aucun changement dans l'état du serveur
	}

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
	send_message("001 " + nick + " :Welcome to the Internet Relay Network " + nick, current_pollfd);  // RPL_WELCOME
	send_message("002 " + nick + " :Your host is irc.server.com, running version 1.0", current_pollfd);  // RPL_YOURHOST

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
