/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:45 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:50:37 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./UserHuman.hpp"

UserHuman::UserHuman(void): User(), Client(), _step_of_link(0)
{
}

UserHuman::UserHuman(std::string & nick, Client & client): User(nick), Client(client), _step_of_link(0)
{
	std::cout << "User Human \"" << PINK << nick << NOCOLOR << "\" is joining" << std::endl;
}


UserHuman::UserHuman(Client & client): User(), Client(client), _step_of_link(0)
{
	std::cout << "User Human \"" << PINK << this->getName() << NOCOLOR << "\" is joining" << std::endl;
}

UserHuman::~UserHuman(){}

void	UserHuman::get_welcolm(const std::string & server_name, Action from_this_action, pollfd &pollfd)
{
	if (_is_init == -1)
		return;
	else if (from_this_action == NICK && _is_init != -1 && _is_init != 1)
		_is_init += 1;
	else if (from_this_action == USER && _is_init != -1 && _is_init != 2)
		_is_init += 2;
	if (_is_init == 3)
	{
		send_message(RPL_WELCOME(server_name, getNick(), getName(), get_ip_to_string()), pollfd);
		send_message(RPL_YOURHOST(server_name, getNick(), "<" + CYAN + "Yassine " + PINK + "Samira " + YELLOW +"Comme"+NOCOLOR+"> 0.1"), pollfd);
		_is_init = -1;
	}
}

void	UserHuman::get_msg_by_step(const std::string & server_name, pollfd &pollfd)
{
	if (_step_of_link == 0)
	{
		send_message(NOTICE(server_name, getNick(), "We verify your nickname and user and the password ..."), pollfd);
		_step_of_link++;
	}
}
