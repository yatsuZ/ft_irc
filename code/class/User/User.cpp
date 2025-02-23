/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/02/23 14:15:32 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void):
 _nick("*"), _name("guest"), _hostname(""), _real_name("Guest"),
  _servername(SERVER_NAME), _mode(NO_MODE), _is_init(0)
{
	// std::cout << "A Default User is joining" << std::endl;
}

User::User(std::string & nick):
 _nick(nick), _name("guest"), _hostname(""), _real_name("Guest"),
  _servername(SERVER_NAME), _mode(NO_MODE), _is_init(0)
{
	// std::cout << "A Parametrick User with nick " << PINK << nick << NOCOLOR << " is joining" << std::endl;
}

User::~User(){}

// --- SETTERS ---
void	User::set_name(const std::string & n)
{_name = n;}

void	User::set_nick(const std::string & n)
{_nick = n;}

void	User::set_hostname(const std::string & h)
{_hostname = h;}

void	User::set_Realname(const std::string & n)
{_real_name = n;}

void	User::set_servername(const std::string & s)
{_servername = s;}

void	User::set_mode(Mode newmode)
{
	if (_mode == newmode)
		_mode = NO_MODE;
	else
		_mode = newmode;
}

// void		User::add_channel(const Channel *c)
// {
// 	for (size_t i=0; i<_channels.size(); i++)
// 	{
// 		if (_channels[i].get_name() == c->get_name())
// 			return ; //TO DO : send message "channel already joined" ?
// 	}
// 	this->_channels.push_back(*c);
// }

void	User::add_chan(size_t idx_of_chan)
{
	_chans.push_back(idx_of_chan);
}