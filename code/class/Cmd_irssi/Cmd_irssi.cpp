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
	// std::cout << "MESSAGE RECU = \"" << MAGENTA << all_message_from_client << NOCOLOR<<"\"";
	std::string delimiteur = " \t\n";
	std::vector<std::string> tokens = ft_split(all_message_from_client, delimiteur);
	size_t	len_of_tokens = tokens.size();
	if (tokens.empty())
		return (std::string());
	for (size_t i = 0; i < len_of_tokens; i++)
	{
		if (is_sep(tokens[i][0], delimiteur) != -1)
			return (tokens[0]);
	}
	
	return (tokens[0]);
}

const std::vector<std::string>	Cmd_irssi::init_arg(std::string &all_message_from_client) const
{
	std::string delimiteur = " \t\n";
	std::vector<std::string> tokens = ft_split(all_message_from_client, delimiteur);
	std::vector<std::string> list_arg;
	size_t	len_of_tokens = tokens.size();
	bool	first_find = false;
	if (this->get_cmd().empty())
		return (list_arg);
	for (std::size_t i = 0; i < tokens.size(); ++i)
	{
		if (is_sep(tokens[i][0], delimiteur) != -1)
		{
			if (first_find)
				list_arg.push_back(tokens[i]);
			else
				first_find = true;
		}
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
	// std::cout << "message = \"" << MAGENTA << all_message_from_client << NOCOLOR << "\"" << std::endl;
	// std::cout << "token[" << 0 << "] = " << this->_cmd << std::endl;
	// for (std::size_t i = 0; i < this->_arg.size(); ++i)
	// {
	// 	std::cout << "token[" << (i + 1) << "] = " << this->_arg[i] << std::endl;
	// }
	// std::cout << "action = " << this->_action_to_do << std::endl;
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
	const std::string &cmd = cmd_irssi.get_cmd();
	const std::vector<std::string> &lst_cmd = cmd_irssi.get_arg();
	size_t taille_de_lst_cmd = lst_cmd.size();
	Action act = cmd_irssi.get_action();

	o << "cmd_irssi = ";
	if (cmd.empty())
		o << CYAN << "Pas de commande et ni d'argument" << NOCOLOR;
	else
	{
		o << "\"" << YELLOW << cmd << NOCOLOR << "\" [ ";
		for (size_t index_arg = 0; index_arg < taille_de_lst_cmd; ++index_arg)
		{
			o << "\"" << GREEN << lst_cmd[index_arg];
			if (index_arg + 1 < taille_de_lst_cmd)
				o << NOCOLOR << "\", ";
			else
				o << NOCOLOR << "]";
		}
	}
	o << "| action a faire : " << RED << act << NOCOLOR;
	return o;
}

Cmd_irssi::Cmd_irssi(Cmd_irssi const & src): _cmd(src.get_cmd()), _arg(src.get_arg()), _action_to_do(src.get_action())
{
}

Cmd_irssi	&Cmd_irssi::operator=(Cmd_irssi const & rf)
{
	if (this != &rf)
	{
		this->_cmd = rf.get_cmd();
		this->_arg = rf.get_arg();
		this->_action_to_do = rf.get_action();
	}
	return (*this);
}
