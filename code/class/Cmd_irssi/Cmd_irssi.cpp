/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd_irssi.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:16:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 01:54:17 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Server/Server.hpp"

const std::string	Cmd_irssi::init_cmd(std::string &all_message_from_client) const
{
	std::string delimiteur = " \t\n";
	std::vector<std::string> tokens = ft_split(all_message_from_client, delimiteur);
	if (tokens.empty())
		return (std::string());
	std::cout << "token[0] = " << tokens[0] << std::endl;
	return (tokens[0]);
}

const std::vector<std::string>	Cmd_irssi::init_arg(std::string &all_message_from_client) const
{
	std::string delimiteur = " \t\n";
	std::vector<std::string> tokens = ft_split(all_message_from_client, delimiteur);
	std::vector<std::string> list_arg;
	for (std::size_t i = 1; i < tokens.size(); ++i)
	{
		list_arg.push_back(tokens[i]);
	}
	return (list_arg);
}

Action	Cmd_irssi::init_action(void) const
{
	if (this->get_cmd() == "exit")
		return (SHUTDOWN);
	return (IDK);
}


Cmd_irssi::Cmd_irssi(): _cmd(), _arg(), _action_to_do(NO_ACTION)
{
}

Cmd_irssi::Cmd_irssi(std::string all_message_from_client):
_cmd(this->init_cmd(all_message_from_client)),
_arg(this->init_arg(all_message_from_client)),
_action_to_do(this->init_action())
{	
}

Cmd_irssi::Cmd_irssi(Action action_to_do): _cmd(), _arg(), _action_to_do()
{
	this->_action_to_do = action_to_do;
}

Cmd_irssi::~Cmd_irssi()
{
}

std::ostream & operator<<( std::ostream & o, Cmd_irssi const & cmd_irssi)
{
	if (cmd_irssi.get_cmd().empty())
		o << getColorCode(CYAN) << "Pas de commande et ni d'argument" << getColorCode(NOCOLOR);
	else
	{
		o << getColorCode(YELLOW) << cmd_irssi.get_cmd() << getColorCode(NOCOLOR) << " " ;
		o << "[ ";
		for (std::vector<std::string>::const_iterator it_arg = cmd_irssi.get_arg().begin();
			it_arg != cmd_irssi.get_arg().end(); ++it_arg)
		{
			o << "\"" << getColorCode(GREEN) << *it_arg;
			if (it_arg + 1 != cmd_irssi.get_arg().end())
				o << getColorCode(NOCOLOR) << "\", ";
		}
		o << "]";
	}
	o << "| action a faire : ";
	o << getColorCode(RED) << getActionString(cmd_irssi.get_action()) << getColorCode(NOCOLOR);
	return o;
}

Cmd_irssi::Cmd_irssi(Cmd_irssi const & src): _cmd(src.get_cmd()), _arg(src.get_arg()), _action_to_do(src.get_action())
{
}

Cmd_irssi	&Cmd_irssi::operator=(Cmd_irssi const & rf)
{
	(void) rf;
	// if (this != &rf)
	return (*this);
}
