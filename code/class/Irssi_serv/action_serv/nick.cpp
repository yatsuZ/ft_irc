/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:23:39 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:43:59 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv Irssi_serv::ft_nick(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	index_of_current_pollfd;
	std::vector<std::string> list_dargument = current_cmd.get_arg();
	std::string nick_user;

	std::cout << PINK << "-------- NICK -----------" << NOCOLOR << std::endl;

	if (current_user == NULL)
		nick_user= "*";
	else
		nick_user = current_user->getNick();

	if (list_dargument.empty())
		return (send_message(ERR_NONICKNAMEGIVEN(this->get_name()), current_pollfd), (NONE));

	std::string new_nick = list_dargument[0];  // Le premier argument de la commande NICK est le surnom

	if (new_nick.empty() || new_nick.length() > 50 || new_nick == "*")
		return (send_message(ERR_ERRONEUSNICKNAME(this->get_name(), new_nick), current_pollfd), (NONE));
	else if (current_user == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), new_nick), current_pollfd), (NONE));
	else if (_nick_already_used(new_nick))
		return (send_message(ERR_NICKNAMEINUSE(this->get_name(), nick_user, new_nick), current_pollfd), (NONE));

	current_user->setNick(new_nick);


	if (current_user->getSet_Nick() == false)
	{
		// send_message(CRLF, current_pollfd);
		current_user->get_welcolm(get_name(), current_cmd.get_action() ,current_pollfd);
	}
	else
	{
		send_message(":" + nick_user + "!~" + current_user->getName() + "@" + this->get_name() + " NICK :" + current_user->getNick() + CRLF, current_pollfd);
		send_message(":" + get_name() + " : Hostname ->" + current_user->get_ip_to_string() + CRLF, current_pollfd);
	}
	
	return (NONE);
}
