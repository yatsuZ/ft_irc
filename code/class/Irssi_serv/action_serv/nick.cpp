/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:23:39 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/12 02:08:10 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv Irssi_serv::ft_nick(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << PINK << "-------- NICK -----------" << NOCOLOR << std::endl;

	std::vector<std::string> list_dargument = current_cmd.get_arg();
	UserHuman *	currentuser = _get_userhuman_by_index_of_pollfd(index_of_current_pollfd);

	std::string nick_user;

	if (currentuser == NULL)
		nick_user= "*";
	else
		nick_user = currentuser->getNick();

	if (list_dargument.empty())
		return (send_message(ERR_NONICKNAMEGIVEN(this->get_name()), current_pollfd), (NONE));

	std::string new_nick = list_dargument[0];  // Le premier argument de la commande NICK est le surnom

	if (new_nick.empty() || new_nick.length() > 50 || new_nick == "*")
		return (send_message(ERR_ERRONEUSNICKNAME(this->get_name(), new_nick), current_pollfd), (NONE));
	else if (currentuser == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), new_nick), current_pollfd), (NONE));
	else if (_nick_already_used(new_nick))
		return (send_message(ERR_NICKNAMEINUSE(this->get_name(), nick_user, new_nick), current_pollfd), (NONE));


	if (new_nick == "*")
		return (send_message(CRLF, current_pollfd), (NONE));

	currentuser->setNick(new_nick);

	if (currentuser->getSet_User() && nick_user == "*")
	{
		send_message("NICK " + currentuser->getNick() + CRLF, current_pollfd);
		send_message(RPL_WELCOME(this->get_name(), currentuser->getNick(), currentuser->getName(), currentuser->get_ip_to_string()), current_pollfd);
		send_message(RPL_YOURHOST(this->get_name(), currentuser->getNick(), std::string(PINK + "<Yassine, Samira , Comme> 0.1" + NOCOLOR)), current_pollfd);
	}
	else
		return (send_message(":" + nick_user + "!" + currentuser->getName() + "@" + this->get_name() + " NICK :" + currentuser->getNick() + CRLF, current_pollfd), (NONE));
	
	return (NONE);
}
