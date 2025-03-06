/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd_irssi.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:16:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/06 14:57:55 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Server/Server.hpp"

//////////////////////////////////////////////////////////// Methode pour defnir les attribut individuellement

const std::string	Cmd_irssi::init_cmd(std::string const &all_message_from_client) const
{
	std::vector<std::string> tokens = ft_split(all_message_from_client, SEPERATOR);
	size_t	len_of_tokens = tokens.size();
	if (tokens.empty())
		return (std::string());
	for (size_t i = 0; i < len_of_tokens; i++)
	{
		if (is_sep(tokens[i][0], SEPERATOR) == -1)
			return (tokens[i]);
	}

	return (std::string());
}

const std::vector<std::string>	Cmd_irssi::init_arg(std::string const &all_message_from_client) const
{
	std::vector<std::string> tokens = ft_split(all_message_from_client, SEPERATOR);
	std::vector<std::string> list_arg;
	bool	first_find = false;

	if (this->get_cmd().empty())
		return (list_arg);

	for (std::size_t i = 0; i < tokens.size(); ++i)
	{
		if (is_sep(tokens[i][0], SEPERATOR) == -1)
		{
			if (first_find)
			{
				list_arg.push_back(tokens[i]);
			}
			else
				first_find = true;
		}
	}

	return (list_arg);
}

Action	Cmd_irssi::init_action(void) const
{
	if (this->get_cmd() == "SHUTDOWN")
		return (SHUTDOWN);
	else if (this->get_cmd() == "NICK")
		return (NICK);
	else if (this->get_cmd() == "CAP")
		return (CAP);
	else if (this->get_cmd() == "USER")
		return (USER);
	else if (this->get_cmd() == "MODE")
		return (MODE);
	else if (this->get_cmd() == "PING")
		return (PING);
	else if (this->get_cmd() == "WHOIS")
		return (WHOIS);
	else if (this->get_cmd() == "QUIT")
		return (QUIT);
	else if (this->get_cmd() == "JOIN")
		return (JOIN);
	else if (this->get_cmd() == "PRIVMSG")
		return (PRIVMSG);
	else if (this->get_cmd() == "KICK")
		return (KICK);
	else if (this->get_cmd() == "INVITE")
		return (INVITE);
	else if (this->get_cmd() == "TOPIC")
		return (TOPIC);
	return (IDK);
}

//////////////////////////////////////////////////////////// Constructeur Destructeur de la class

Cmd_irssi::Cmd_irssi(): _cmd(""), _arg(std::vector<std::string>()), _action_to_do(NO_ACTION), _all_line("")
{
}

Cmd_irssi::Cmd_irssi(std::string all_message_from_client):
_cmd(this->init_cmd(all_message_from_client)),
_arg(this->init_arg(all_message_from_client)),
_action_to_do(this->init_action()),
_all_line(all_message_from_client)
{
}

Cmd_irssi::Cmd_irssi(Action action_to_do): _cmd(""), _arg(std::vector<std::string>()), _action_to_do(action_to_do), _all_line("")
{
	// this->_action_to_do = action_to_do;
	// std::cout << "Construction par action" << std::endl;
	// std::cout << *this << std::endl;

}

Cmd_irssi::Cmd_irssi(Cmd_irssi const & src): _cmd(src.get_cmd()), _arg(src.get_arg()), _action_to_do(src.get_action()), _all_line(src.get_all_line())
{
}

Cmd_irssi	&Cmd_irssi::operator=(Cmd_irssi const & rf)
{
	if (this != &rf)
	{
		// this->_cmd = rf.get_cmd();
		// this->_arg = rf.get_arg();
		this->_action_to_do = rf.get_action();
	}
	return (*this);
}

Cmd_irssi::~Cmd_irssi()
{
}

std::string	Cmd_irssi::get_message(void) const
{
	std::string str = _all_line;

	// Supprimer '\r' et '\n' manuellement
	for (std::string::iterator it = str.begin(); it != str.end(); ) {
		if (*it == '\r' || *it == '\n')
			it = str.erase(it); // erase retourne l'itérateur suivant
		else
			++it;
	}

	// Trouver ':' et supprimer tout ce qui est avant
	std::string::size_type pos = str.find(':');
	if (pos != std::string::npos)
		str = str.substr(pos + 1); // Garde seulement ce qui est après ':'
	else
		return ("");
	return (str);
}
