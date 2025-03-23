/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:35:23 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/23 16:45:17 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(int argc, char **argv)
{
	std::cout << BPNK << "### Création du bot..." << RST << std::endl;
	if (argc != 2)
		throw InitException("==== Error: configuration file recquired.");
	_parse(argv[1]);
	init();
	(void)argv;

}

Bot::~Bot()
{
	if (_socketfd == -1)
		close(_socketfd);
	std::cout << BCYN << "### GOOD BYE ^^!" << RST << std::endl;
}

void	Bot::init()
{
	std::cout << BPNK <<"### Connexion au serveur..." << _nick << RST << std::endl;

	const sockaddr	*sock_addr_ptr = reinterpret_cast<const sockaddr *>(&_sock_addr);
	// (void)sock_addr_ptr;
	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd == -1)
		_throw_msg("==== Error: socket creation failed... -1");
	
	_sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(_port);

	if (connect(_socketfd, sock_addr_ptr, sizeof(*sock_addr_ptr)) == -1)
		throw InitException("====Error: can't connect to the server");	

	_connexion();
	//connexion au serveur
	std::cout << BCYN << "### Bot connected succesfully !" << RST << std::endl;
	//to do: faire tourner le bot tant que le serv est acitf ou ctrl-c/disconnect pas call
}

//send toutes les infos de connexion en tant qu'userBot au serveur
void	Bot::_connexion()
{	

	//CMDS IRC pour établir une connexion en tant qu'user en tant qu'user
	send_message("PASS " + _password + CRLF);
	send_message("NICK " + _nick + CRLF);
	send_message("USER " + _username + " " + _hostname + " " + _ip + " :" + _realname +  CRLF);
}

void	Bot::_disconnect()
{	
	close(_socketfd);
	return ;
}

uint16_t	Bot::_valid_port(std::string p)	//check si port valide
{
	long		port = atol(p.c_str());

	if (port < 1 || port > 65535)
		throw InitException("==== Error: Invalid Port (number should be between 1 and 65535).");

	return (static_cast<uint16_t>(port));
}

//excpetion message
void	Bot::_throw_msg(const std::string & m)
{
	if (_socketfd == -1)
		close(_socketfd);
	throw InitException(m);
}

void	Bot::send_message(const std::string & message)
{
	send(_socketfd, message.c_str(), message.size(), 0);
}