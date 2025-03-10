/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:23:39 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 14:56:36 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"


/*
   <target>     ::= <to> [ "," <target> ]
   <to>         ::= <channel> | <user> '@' <servername> | <nick> | <mask>
   <channel>    ::= ('#' | '&') <chstring>
   <servername> ::= <host>
   <host>       ::= see RFC 952 [DNS:4] for details on allowed hostnames
   <nick>       ::= <letter> { <letter> | <number> | <special> }
   <mask>       ::= ('#' | '$') <chstring>
   <chstring>   ::= <any 8bit code except SPACE, BELL, NUL, CR, LF and <============== 
                     comma (',')> <================

   Other parameter syntaxes are:

   <user>       ::= <nonwhite> { <nonwhite> }
   <letter>     ::= 'a' ... 'z' | 'A' ... 'Z'
   <number>     ::= '0' ... '9'
   <special>    ::= '-' | '[' | ']' | '\' | '`' | '^' | '{' | '}'  <==============
	
 */

//renvoie 1 si nick contient un caractere non autorisée
bool Irssi_serv::_err_nick(std::string & nick) const
{
	std::string start_with = "$:#&";
	std::string contain = " ,*?!@.";

	for (size_t i=0; i<start_with.size(); i++)
	{
		if (nick[0] == start_with[i])
			return (1);
	}

	for (size_t i=0; i<contain.size(); i++)
	{
		if (nick.find(contain[i]) != std::string::npos)
			return (1);
	}

	return (0);
}

Reaction_Serv	Irssi_serv::ft_nick(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::vector<std::string> list_dargument = current_cmd.get_arg();
	std::string nick_user;

	std::cout << PINK << "-------- NICK -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	if (list_dargument.empty())
		return (send_message(ERR_NONICKNAMEGIVEN(this->get_name()), current_pollfd), (NONE));

	if (current_user == NULL)
		nick_user= list_dargument[0];
	else
		nick_user = current_user->get_nick();

	std::string new_nick = list_dargument[0];  // Le premier argument de la commande NICK est le surnom

	if (new_nick.empty() || new_nick.length() > 9 || new_nick == "*")
		return (send_message(ERR_ERRONEUSNICKNAME(this->get_name(), new_nick), current_pollfd), (NONE));
	else if (current_user == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), new_nick), current_pollfd), (NONE));
	else if (_nick_already_used(new_nick))
		return (send_message(ERR_NICKNAMEINUSE(this->get_name(), nick_user, new_nick), current_pollfd), (NONE));

	if (_err_nick(new_nick))
		return (send_message(ERR_ERRONEUSNICKNAME(this->get_name(), new_nick), current_pollfd), (NONE));

	current_user->set_nick(new_nick);

	if (current_user->get_Set_Nick() == false)
	{
		// send_message(CRLF, current_pollfd);
		current_user->get_welcolm(get_name(), current_cmd.get_action() ,current_pollfd);
	}
	else
	{
		send_message(":" + nick_user + "!~" + current_user->get_name() + "@" + this->get_name() + " NICK :" + current_user->get_nick() + CRLF, current_pollfd);
		send_message(":" + get_name() + " : Hostname ->" + current_user->get_ip_to_string() + CRLF, current_pollfd);
	}
	
	return (NONE);
}