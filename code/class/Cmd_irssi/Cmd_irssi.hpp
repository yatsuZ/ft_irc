/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd_irssi.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:01:10 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/28 19:45:23 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Ft_irc.hpp"
#include "./../User/UserHuman/UserHuman.hpp"

class Cmd_irssi
{
private:
const std::string					_cmd;
const std::vector<std::string>		_arg;
Action						_action_to_do;
const std::string					_all_line;
//	Utilisateur	_autor;
const std::string				init_cmd(std::string &all_message_from_client) const;
const std::vector<std::string>	init_arg(std::string &all_message_from_client) const;
Action							init_action(void) const;
public:
	Cmd_irssi();
	Cmd_irssi(Cmd_irssi const & src);
	Cmd_irssi	&operator=(Cmd_irssi const & rf);
	Cmd_irssi(std::string all_message_from_client);
	Cmd_irssi(Action action_to_do);
	~Cmd_irssi();
	
	Action						get_action(void) const { return this->_action_to_do;}
	std::string					get_cmd(void) const { return this->_cmd;}
	std::vector<std::string>	get_arg(void) const { return this->_arg;}
	std::string					get_all_line(void) const {return this->_all_line;};
	std::string					get_message(void) const;
};

std::ostream & operator<<( std::ostream & o, Cmd_irssi const & cmd_irssi);
