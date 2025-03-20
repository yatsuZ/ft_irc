/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:35:23 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/20 15:36:20 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot() :
_nick("Bob"),
_username("bobby"),
_realname("Bobby Shmurda"),
_ip(ADRESSE)
{
	std::cout << "### Initialisation du bot " << _nick << std::endl;

	_valid_port();
}

Bot::~Bot()
{std::cout << "### GOOD BYE ^^!" << std::endl;}


void	Bot::init()
{
	// int opt = REUSEADDR_OPTION;
	const sockaddr	*sock_addr_ptr = reinterpret_cast<const sockaddr *>(&_sock_addr);

	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd == -1)
		_throw_msg("==== Error: socket creation failed... -1");
	
	_sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(_port);

	if (connect(_socketfd, server_addr, ))
		throw InitException("====Error: can't connect to the server");	

// 	// l'option empeche de bin s'il y a deja une ecoute sur la socket lié a l'adresse
// 	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
// 		throw InitException("==== Error: can't config SO_REUSEADDR");

// 	//operations non bloquante
// 	if (fcntl(_socketfd, F_SETFL, O_NONBLOCK) < 0)
// 		throw InitException("==== Error: attempt O_NONBLOCK mode failed.");

// 	//liaison de la socket a l'adresse et au port
	// if (bind(_socketfd, sock_addr_ptr, sizeof(_sock_addr)) < 0)
	// 	throw InitException("==== Error: Bind failed.");

	//connexion au serveur
	std::cout << "### Bot connected succesfully !" << std::endl;
}

void	Bot::_disconnect()
{	
	close(_socketfd);
	return ;
}

void	Bot::_valid_port()	//check ip et port valide
{
	long		port = atol("8080");

	if (port > 65535 || port < 1)
		throw InitException("==== Error: Invalid Port (number should be between 1 and 65535).");

	_port = static_cast<uint16_t>(port);
}

void	Bot::_throw_msg(const std::string & m)
{
	if (_socketfd == -1)
		close(_socketfd);
	throw InitException(m);
}